--TEST--
Check for util array_last_key
--SKIPIF--
<?php if (!extension_loaded("util")) print "skip"; ?>
--FILE--
<?php
$arr = ['php', 'C++', 'c', 'java'];
echo Util::array_last_key($arr), "\n";

$arr = ['b' => 'apple', 'a' => 'pear'];
echo Util::array_last_key($arr), "\n";
?>
--EXPECT--
3
a
