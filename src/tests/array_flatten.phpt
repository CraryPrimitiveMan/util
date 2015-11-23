--TEST--
Check for util array_flatten
--SKIPIF--
<?php if (!extension_loaded("util")) {
    print "skip";
} ?>
--FILE--
<?php
$arr = ['a', 'b', ['c', 'd', 'e', ['f', 'g', [[[['h', 'i', 'j']]]]]]];
var_dump(Util::array_flatten($arr));

$arr = ['a' => 'a', 'b', ['c' => 'c', 'd', 'e', ['f' => 'f', 'g', [[[['h', 'i', 'j' => 'j']]]]]]];
var_dump(Util::array_flatten($arr));

var_dump(Util::array_flatten($arr, false));
?>
--EXPECT--
array(10) {
  [0]=>
  string(1) "a"
  [1]=>
  string(1) "b"
  [2]=>
  string(1) "c"
  [3]=>
  string(1) "d"
  [4]=>
  string(1) "e"
  [5]=>
  string(1) "f"
  [6]=>
  string(1) "g"
  [7]=>
  string(1) "h"
  [8]=>
  string(1) "i"
  [9]=>
  string(1) "j"
}
array(10) {
  ["a"]=>
  string(1) "a"
  [0]=>
  string(1) "b"
  ["c"]=>
  string(1) "c"
  [1]=>
  string(1) "d"
  [2]=>
  string(1) "e"
  ["f"]=>
  string(1) "f"
  [3]=>
  string(1) "g"
  [4]=>
  string(1) "h"
  [5]=>
  string(1) "i"
  ["j"]=>
  string(1) "j"
}
array(10) {
  [0]=>
  string(1) "a"
  [1]=>
  string(1) "b"
  [2]=>
  string(1) "c"
  [3]=>
  string(1) "d"
  [4]=>
  string(1) "e"
  [5]=>
  string(1) "f"
  [6]=>
  string(1) "g"
  [7]=>
  string(1) "h"
  [8]=>
  string(1) "i"
  [9]=>
  string(1) "j"
}
