--TEST--
Check for util array_first_key
--SKIPIF--
<?php if (!extension_loaded("util")) {
    print "skip";
} ?>
--FILE--
<?php
$arr = ['php', 'C++', 'c', 'java'];
echo Util::array_first_key($arr), "\n";

$arr = ['b' => 'apple', 'a' => 'pear'];
echo Util::array_first_key($arr), "\n";
?>
--EXPECT--
0
b
