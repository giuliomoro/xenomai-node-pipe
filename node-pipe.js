const fs = require("fs")
const util = require('util');
// hardcode the defines from stru.h
//#define SHM_NAME "/myshared"
const pipeName= "/proc/xenomai/registry/native/pipes/mypipe"

const fd = fs.openSync(pipeName, "r+")
console.log("fd: ", fd)
var size = fs.fstatSync(fd).size // no idea why this requires SHM_NAME: the specs require "int fd" as the only argument
console.log("File size: ", size)

setInterval(function(){
	console.log("w")
	var buffer = new Buffer(100);
	var ret = fs.writeSync(fd, "node\n\0"); 
	console.log(util.format("Written %d bytes", ret));
}, 1000);

setInterval(function(){
	var size = 1000;
	var buffer = new Buffer(size);
	console.log("r");
	ret = fs.read(fd, buffer, 0, size, 0, function(err, bytesRead, buffer){
		console.log("Received: ", bytesRead, "bytes");
		console.log("name: ", buffer.toString("utf8", 0, bytesRead));
	});
}, 1100);
return 0;

const floatSize = 4;
for(var n = valuesStart; n < size; n+=floatSize){
	console.log(util.format("values[%d]: %d", (n-valuesStart)/floatSize , buf.readFloatLE(n)));
}
