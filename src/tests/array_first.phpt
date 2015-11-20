--TEST--
Check for util array_first
--SKIPIF--
<?php if (!extension_loaded("util")) print "skip"; ?>
--FILE--
<?php
$arr = ['php', 'C++', 'c', 'java'];
echo Util::array_first($arr), "\n";

$arr = ['b' => 'apple', 'a' => 'pear'];
echo Util::array_first($arr), "\n";
?>
--EXPECT--
php
apple
