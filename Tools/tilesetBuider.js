const fs = require('fs');
const PNG = require('node-png').PNG;
const path = require('path');

const EXT_FILTER = ".png"
const MAP_RES = 1024;

const inputPaths = [
	"./Bin/assets/char",
	"./Bin/assets/items",
	"./Bin/assets/tiles"
];

function toCamelCase(str) {
  // Lower cases the string
  return str.toLowerCase()
    // Replaces any - or _ characters with a space 
    .replace( /[-_]+/g, ' ')
    // Removes any non alphanumeric characters 
    .replace( /[^\w\s]/g, '')
    // Uppercases the first character in each group immediately following a space 
    // (delimited by spaces) 
    .replace( / (.)/g, function($1) { return $1.toUpperCase(); })
    // Removes spaces 
    .replace( / /g, '' );
}

const walkSync = function(dir, filelist, filter) {
  const files = fs.readdirSync(dir);
  filelist = filelist || [];
  files.forEach((file)=>{
	const fp = dir + "/" + file;
    if (fs.statSync(fp).isDirectory()) {
      filelist = walkSync(dir + "/" + file, filelist, filter);
    }
    else {
	  if(filter){
		if(filter === path.extname(fp)) filelist.push([dir, file]);
	  }	else filelist.push([dir, file]);
    }
  });
  return filelist;
};

const getTiles = function(paths, filter) {
	let tiles = [];
	for(let i = 0; i < paths.length; i++) {

		const list = walkSync(paths[i], [], filter).map((i)=>{
			const fname = i[0].replace("./Bin/assets/", "").replace("/", "_") + "_" + i[1];
			const name = fname.replace(path.extname(fname), "");
			return [name, i[0] + "/" + i[1]];
		});
		
		console.log(list)
		
		tiles = tiles.concat(list.map((t)=>{
			return [ "TT_" + t[0].toUpperCase(), t[1] ];
		}));
	}
	return tiles;
}

const readPNG = function(path, callback) {
	return new Promise((res,rej)=>{
		fs.createReadStream(path)
			.pipe(new PNG({
				filterType: 4
			}))
			.on('parsed', function() {
				res(this.data);
			});
	});
}

const putImage = function(dst, dx, dy, dw, dh, src, sw, sh) {
	
	for(let y = 0; y < sh; y++){
		for(let x = 0; x < sw; x++){
			const sidx = (sw * y + x) << 2;
			
			const didx = (dw * (y + dy) + (x + dx)) << 2;
			
			// color
            dst[didx]   = src[sidx];
            dst[didx+1] = src[sidx+1];
            dst[didx+2] = src[sidx+2];

            // and opacity
            dst[didx+3] = src[sidx+3];
		}	
	}
	
}


async function RUN() {
	const list = getTiles(inputPaths, EXT_FILTER);

	
	
	const out = new PNG({width:MAP_RES, height:MAP_RES});

	if(Math.sqrt(list.length) * 32 > MAP_RES) {
		throw "Size error";
	}
	
	let enumText = "/* DONT EDIT THIS : Auto generating */\n";
	enumText += "#pragma once \n";
	enumText += "enum eTiles { \n";
	
	for(let tI = 0; tI < list.length; tI++) {
		const data = await readPNG(list[tI][1]);
		const x = Math.floor((32 * tI) % 1024);		
		const y = Math.floor((32 * tI) / 1024);
		
		enumText += list[tI][0] + ",\n";
		
		putImage(out.data,x,y*32,MAP_RES,MAP_RES, data, 32, 32);
	}
	
	enumText += "};\n"
	
	out.pack().pipe(fs.createWriteStream('./Bin/assets/tileset.png'));
	fs.writeFileSync("./Source/eTiles.h", enumText);
	
}

RUN();