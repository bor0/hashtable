var fs = require('fs');
var readline = require('readline');
var stream = require('stream');

var instream = fs.createReadStream('strings.txt');
var outstream = new stream;
var rl = readline.createInterface(instream, outstream);
var ht = {};

rl.on('line', function(line) {
  // process line here
  ht[line] = line;
});

rl.on('close', function() {
  // do something on finish here
  console.log(ht['pffevnoghq']);
});
