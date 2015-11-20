--TEST--
Check for util array_last
--SKIPIF--
<?php if (!extension_loaded("util")) print "skip"; ?>
--FILE--
<?php
$arr = ['php', 'C++', 'c', 'java'];
echo Util::array_last($arr), "\n";

$arr = ['b' => 'apple', 'a' => 'pear'];
echo Util::array_last($arr), "\n";
?>
--EXPECT--
java
pear
