#pragma once

#include <vector>
#include <queue>
#include <memory>

#include "Rect.h"

namespace BWG {
   namespace Utils {

      const int QT_MAX_PER_NODE = 32; // Maximun number of points per node before subdividing
      const int QT_MAX_DEPTH = 64;    // Maximum depth to allow before dumping all additional points into the leaf node

      template<typename SelfType>
      struct Point
      {
         std::unique_ptr<SelfType> type;
         int x;
         int y;

         Point() {}
         Point(const Point&) {}

         Point(std::unique_ptr<SelfType> _type, int _x, int _y) : type(std::move(_type)), x(_x), y(_y) {}

         bool operator()(const Point& l, const Point& r)
         {
            return l.rank < r.rank;
         }
      };
            
      // true if r1 intersects r2
      static bool inline rects_intersect(const Rect& r1, const Rect& r2) {
         if(r2.lx > r1.hx || r2.ly > r1.hy || r2.hx < r1.lx || r2.hy < r1.ly)
            return false;

         return true;
      }

      // true if r1 fully contains r2
      static bool inline rects_contained(const Rect& r1, const Rect& r2) {
         if((r1.lx <= r2.lx && r1.hx >= r2.hx) && r1.ly <= r2.ly && r1.hy >= r2.hy) return true;

         return false;
      }

      // true if r contains p
      template<typename SelfType>
      static bool inline pt_contained(const Rect& r, const Point<SelfType>* p) {
         return (r.lx <= p->x && r.hx >= p->x) && (r.ly <= p->y && r.hy >= p->y);
      }

      template<typename SelfType>
      static inline void print_point(const Point<SelfType>& p) {
         printf("[Point x=%f y=%f]\n", p.x, p.y);
      }

      static inline void print_rect(Rect& rect) {
         printf("[Rect  %4.d %4.d  %4.d %4.d]\n", rect.lx, rect.hx, rect.ly, rect.hy);
      }

      
      template<typename Type>
      struct QuadTree {
         Rect bounds;  // 2D Rectangular bounds of this node
         int depth;    // Depth of this node in the tree

         std::unique_ptr<QuadTree<Type>> nw;  // Northwest subdivision quadrant
         std::unique_ptr<QuadTree<Type>> ne;  // Northeast subdivision quadrant
         std::unique_ptr<QuadTree<Type>> sw;  // Southwest subdivision quadrant
         std::unique_ptr<QuadTree<Type>> se;  // Southeast subdivision quadrant

         using DataType = Type;
         using PointType = Point<Type>;
         using PtsType = std::vector<std::unique_ptr<PointType>>;

         using QueryResult = std::priority_queue<PointType*, std::vector<PointType*>>;

         PtsType pts; // Points in this node

         QuadTree() : depth(0), nw(nullptr), sw(nullptr), ne(nullptr), se(nullptr)
         { }

         QuadTree(Rect _bounds, int _depth) : bounds(_bounds), depth(_depth), nw(nullptr), sw(nullptr), ne(nullptr), se(nullptr)
         { }

         bool Insert(std::unique_ptr<PointType> point)
         {
            return Insert(this, std::move(point));
         }
  
         bool Insert(QuadTree<Type>* node, std::unique_ptr<PointType> point)
         {
            // If this point is outside the bounds of this node, return false early
            if(!pt_contained(node->bounds, point.get())) {
               return false;
            }

            // If we have subdivided, add to the children
            if(node->nw != 0) {

               if(Insert(node->nw.get(), std::move(point)))
                  return true;

               if(node->ne != 0)
                  if(Insert(node->ne.get(), std::move(point)))
                     return true;

               if(node->sw != 0)
                  if(Insert(node->sw.get(), std::move(point)))
                     return true;

               if(node->se != 0)
                  if(Insert(node->se.get(), std::move(point)))
                     return true;

               return false;

            }
            else {
               // If we haven't subdivided and we haven't reached the max number of points for this node OR we have reached the maximum depth already,
               // then add the point to this leaf node
               if(node->pts.size() < QT_MAX_PER_NODE || node->depth >= QT_MAX_DEPTH) {
                  node->pts.push_back(std::move(point));
                  return true;

                  // Otherwise we subdivide and add the point to the child node it belongs in
               }
               else {
                  Subdivide(node);

                  // Don't re-assign the points to new nodes;
                  // since the points are inserted already sorted by rank, the lowest ranks will always be first to be checked
                  //
                  //            while (node->pts.size() > 0) {
                  //                Point* p = node->pts.back();
                  //                node->pts.pop_back();
                  //                quadtree_insert(node, *p);
                  //            }

                  // Re-call the insert on this node -- since we have now subdivided the tree,
                  // it will go into one of the new child nodes
                  return Insert(node, std::move(point));
               }
            }

            return false;
         }

         void Subdivide(QuadTree<Type>* parent) {
            if(parent->nw == 0) {
               Rect nw_bounds, ne_bounds, sw_bounds, se_bounds;

               // Calculate the child NW bounds
               nw_bounds.lx = parent->bounds.lx;
               nw_bounds.hx = parent->bounds.lx + ((parent->bounds.hx - parent->bounds.lx) / 2);
               nw_bounds.ly = parent->bounds.ly + ((parent->bounds.hy - parent->bounds.ly) / 2);
               nw_bounds.hy = parent->bounds.hy;

               parent->nw = std::make_unique<QuadTree>(nw_bounds, parent->depth + 1);

               // Calculate the child NE bounds
               ne_bounds.lx = parent->bounds.lx + ((parent->bounds.hx - parent->bounds.lx) / 2);
               ne_bounds.hx = parent->bounds.hx;
               ne_bounds.ly = parent->bounds.ly + ((parent->bounds.hy - parent->bounds.ly) / 2);
               ne_bounds.hy = parent->bounds.hy;

               parent->ne = std::make_unique<QuadTree<Type>>(ne_bounds, parent->depth + 1);

               // Calculate the child SW bounds
               sw_bounds.lx = parent->bounds.lx;
               sw_bounds.hx = parent->bounds.lx + ((parent->bounds.hx - parent->bounds.lx) / 2);
               sw_bounds.ly = parent->bounds.ly;
               sw_bounds.hy = parent->bounds.ly + ((parent->bounds.hy - parent->bounds.ly) / 2);

               parent->sw = std::make_unique<QuadTree<Type>>(sw_bounds, parent->depth + 1);

               // Calculate the child SE bounds
               se_bounds.lx = parent->bounds.lx + ((parent->bounds.hx - parent->bounds.lx) / 2);
               se_bounds.hx = parent->bounds.hx;
               se_bounds.ly = parent->bounds.ly;
               se_bounds.hy = parent->bounds.ly + ((parent->bounds.hy - parent->bounds.ly) / 2);

               parent->se = std::make_unique<QuadTree<Type>>(se_bounds, parent->depth + 1);
            }
         }

         void GetSubtree(QuadTree<Type>* node, QueryResult& results, int& ct) {
            // Add all points within this node to the search results container
            for(auto& point : node->pts) {
               results.push(point.get());
               ct++;
            }

            // Return all results in the child nodes of this node
            if(node->nw != 0) {
               GetSubtree(node->nw.get(), results, ct);
               GetSubtree(node->ne.get(), results, ct);
               GetSubtree(node->sw.get(), results, ct);
               GetSubtree(node->se.get(), results, ct);
            }
         }
         
         void SearchQuad(const Rect query, QueryResult& results, int& ct) {
            SearchQuad(this, query, results, ct);
         }

         void SearchQuad(QuadTree<Type>* node, const Rect query, QueryResult& results, int& ct) {

            // If this node is fully contained within the search query, return all points in tree below this node
            if(rects_contained(query, node->bounds)) {
               GetSubtree(node, results, ct);
            }
            // If this node's boundary rectangle intersects with the query rectangle, then check all points in this node for containment
            // and add to the results container when inside the search rect
            else if(rects_intersect(node->bounds, query)) {

               for(auto& point : node->pts) {
                  if(pt_contained(query, point.get())) {
                     results.push(point.get());
                     ct++;
                  }
               }

               // If there was an intersection, then recursively search the child nodes
               if(node->nw != 0) {
                  SearchQuad(node->nw.get(), query, results, ct);
                  SearchQuad(node->ne.get(), query, results, ct);
                  SearchQuad(node->sw.get(), query, results, ct);
                  SearchQuad(node->se.get(), query, results, ct);
               }
            }
            // Else no intersection and no containment, stop recursing the tree
         }

      };

      /*

      // Create a quadtree node, initialized with bounds and depth
      template<typename QT_TYPE>
      static QuadTree<QT_TYPE>* quadtree_construct(Rect bounds, int depth) {
         QuadTree<QT_TYPE>* node = new QuadTree<QT_TYPE>();
         node->bounds = bounds;
         node->depth = depth;
         node->nw = 0;
         node->ne = 0;
         node->sw = 0;
         node->se = 0;
         return node;
      }

      // Delete a root quadtree node and all child nodes
      template<typename QT_TYPE>
      static void quadtree_delete(QuadTree<QT_TYPE>* root) {
         if(root != 0) {
            quadtree_delete(root->nw);
            if(root->ne != 0)
               quadtree_delete(root->ne);
            if(root->sw != 0)
               quadtree_delete(root->sw);
            if(root->se != 0)
               quadtree_delete(root->se);

            delete root;
            root = 0;
         }
      }

      // Forward declaration of internal quadtree_insert method (below)
      template<typename QT_TYPE>
      static bool quadtree_insert(QuadTree<QT_TYPE>* node, QT_TYPE* p);

      // Helper method to insert a vector of points at once
      // For the Churchill Navigation challenge, these points are sorted in ascending order by their Rank value,
      // assuring we always have the lowest ranked nodes at the top level of the tree when searching breadth first
      template<typename QT_TYPE>
      static void quadtree_insert(QuadTree<QT_TYPE>* root, std::vector<QT_TYPE*>& points, int& ct) {
         for(std::vector<Point*>::iterator it = points.begin(); it != points.end(); ++it) {
            quadtree_insert(root, *it);
            ct++;
         }
      }

      // Helper method to print out a quadtree node and it's child nodes
      template<typename QT_TYPE>
      static inline void quadtree_print(QuadTree<QT_TYPE>* node) {
         printf("QT %.*s depth=%d lx=%d hx=%d ly=%d hy=%d pts=%d \n",
            node->depth, "                                               ",
            node->depth, node->bounds.lx, node->bounds.hx, node->bounds.ly, node->bounds.hy, node->pts.size());
         if(node->nw != 0) {
            quadtree_print(node->nw);
            if(node->ne != 0)
               quadtree_print(node->ne);
            if(node->sw != 0)
               quadtree_print(node->sw);
            if(node->se != 0)
               quadtree_print(node->se);
         }
      }

      // Return all points within this node and all of it's children
      // This is used when the boundary is fully contained within the search
      // range and further rect intersection/containment checks are no longer needed
      template<typename QT_TYPE>
      static inline void quadtree_return_subtree(QuadTree<QT_TYPE>* node, std::priority_queue<QT_TYPE*, std::vector<QT_TYPE*>>& results, int& ct) {

         // Add all points within this node to the search results container
         for(std::vector<Point*>::iterator it = node->pts.begin(); it != node->pts.end(); ++it) {
            if(results.size() < 20) {
               results.push(*it);
               ct++;
            }
            else if(results.top()->rank > (*it)->rank) {
               results.pop();
               results.push(*it);
               ct++;
            }
         }

         // Return all results in the child nodes of this node
         if(node->nw != 0) {
            quadtree_return_subtree(node->nw, results, ct);
            quadtree_return_subtree(node->ne, results, ct);
            quadtree_return_subtree(node->sw, results, ct);
            quadtree_return_subtree(node->se, results, ct);
         }
      }

      // Depth first search the quadtree node (root) for all points within query Rect, add them to the results container
      // Top level points in the tree will always have the lowest ranks in that boundary, if we get to 20 (max search result count) we can stop searching
      template<typename QT_TYPE>
      static inline void quadtree_search(QuadTree<QT_TYPE>* node, const Rect query, std::priority_queue<QT_TYPE*, std::vector<QT_TYPE*>>& results, int& ct) {

         // If this node is fully contained within the search query, return all points in tree below this node
         if(rects_contained(query, node->bounds)) {
            quadtree_return_subtree(node, results, ct);
         }
         // If this node's boundary rectangle intersects with the query rectangle, then check all points in this node for containment
         // and add to the results container when inside the search rect
         else if(rects_intersect(node->bounds, query)) {
            for(std::vector<QT_TYPE*>::iterator it = node->pts.begin(); it != node->pts.end(); ++it) {
               if(pt_contained(query, **it)) {
                  if(results.size() < 20) {
                     results.push(*it);
                     ct++;
                  }
                  else if(results.top()->rank > (*it)->rank) {
                     results.pop();
                     results.push(*it);
                     ct++;
                  }
               }
            }

            // If there was an intersection, then recursively search the child nodes
            if(node->nw != 0) {
               quadtree_search(node->nw, query, results, ct);
               quadtree_search(node->ne, query, results, ct);
               quadtree_search(node->sw, query, results, ct);
               quadtree_search(node->se, query, results, ct);
            }
         }
         // Else no intersection and no containment, stop recursing the tree
      }

      // Subdivides this quadtree node assuming a left->right, bottom->up coordinate system
      //       |
      //       . (0,1)      . (1,1)
      //       |
      //       |
      //       |
      //_______.____________. (1,0)
      //       | (0,0)
      //       |
      template<typename QT_TYPE>
      static inline void quadtree_subdivide(QuadTree<QT_TYPE>* parent) {
         if(parent->nw == 0) {
            Rect nw_bounds, ne_bounds, sw_bounds, se_bounds;

            // Calculate the child NW bounds
            nw_bounds.lx = parent->bounds.lx;
            nw_bounds.hx = parent->bounds.lx + ((parent->bounds.hx - parent->bounds.lx) / 2);
            nw_bounds.ly = parent->bounds.ly + ((parent->bounds.hy - parent->bounds.ly) / 2);
            nw_bounds.hy = parent->bounds.hy;

            parent->nw = quadtree_construct(nw_bounds, parent->depth + 1);

            // Calculate the child NE bounds
            ne_bounds.lx = parent->bounds.lx + ((parent->bounds.hx - parent->bounds.lx) / 2);
            ne_bounds.hx = parent->bounds.hx;
            ne_bounds.ly = parent->bounds.ly + ((parent->bounds.hy - parent->bounds.ly) / 2);
            ne_bounds.hy = parent->bounds.hy;

            parent->ne = quadtree_construct(ne_bounds, parent->depth + 1);

            // Calculate the child SW bounds
            sw_bounds.lx = parent->bounds.lx;
            sw_bounds.hx = parent->bounds.lx + ((parent->bounds.hx - parent->bounds.lx) / 2);
            sw_bounds.ly = parent->bounds.ly;
            sw_bounds.hy = parent->bounds.ly + ((parent->bounds.hy - parent->bounds.ly) / 2);

            parent->sw = quadtree_construct(sw_bounds, parent->depth + 1);

            // Calculate the child SE bounds
            se_bounds.lx = parent->bounds.lx + ((parent->bounds.hx - parent->bounds.lx) / 2);
            se_bounds.hx = parent->bounds.hx;
            se_bounds.ly = parent->bounds.ly;
            se_bounds.hy = parent->bounds.ly + ((parent->bounds.hy - parent->bounds.ly) / 2);

            parent->se = quadtree_construct(se_bounds, parent->depth + 1);
         }
      }

      // Insert a point into the quadtree
      template<typename QT_TYPE>
      static inline bool quadtree_insert(QuadTree<QT_TYPE>* node, QT_TYPE* p) {
         // If this point is outside the bounds of this node, return false early
         if(!pt_contained(node->bounds, *p)) {
            return false;
         }

         // If we have subdivided, add to the children
         if(node->nw != 0) {

            if(quadtree_insert(node->nw, p))
               return true;

            if(node->ne != 0)
               if(quadtree_insert(node->ne, p))
                  return true;

            if(node->sw != 0)
               if(quadtree_insert(node->sw, p))
                  return true;

            if(node->se != 0)
               if(quadtree_insert(node->se, p))
                  return true;

            return false;

         }
         else {
            // If we haven't subdivided and we haven't reached the max number of points for this node OR we have reached the maximum depth already,
            // then add the point to this leaf node
            if(node->pts.size() < QT_MAX_PER_NODE || node->depth >= QT_MAX_DEPTH) {
               node->pts.push_back(p);
               return true;

               // Otherwise we subdivide and add the point to the child node it belongs in
            }
            else {
               quadtree_subdivide(node);

               // Don't re-assign the points to new nodes;
               // since the points are inserted already sorted by rank, the lowest ranks will always be first to be checked
               //
               //            while (node->pts.size() > 0) {
               //                Point* p = node->pts.back();
               //                node->pts.pop_back();
               //                quadtree_insert(node, *p);
               //            }

               // Re-call the insert on this node -- since we have now subdivided the tree,
               // it will go into one of the new child nodes
               return quadtree_insert(node, p);
            }
         }

         return false;
      }
      */
   }
}