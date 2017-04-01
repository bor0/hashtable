/*
 * This file is part of Hashtable.
 * Hashtable is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hashtable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hashtable.  If not, see <http://www.gnu.org/licenses/>.
*/

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
