--TEST--
Check for util array_first
--SKIPIF--
<?php if (!extension_loaded("util")) {
    print "skip";
} ?>
--FILE--
<?php
$arr = ['name' => 'harry'];
echo Util::array_get($arr, 'action', 'index'), "\n";
echo Util::array_get($arr, 'name', 'tom'), "\n";
?>
--EXPECT--
index
harry
