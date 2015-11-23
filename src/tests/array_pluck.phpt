--TEST--
Check for util array_pluck
--SKIPIF--
<?php if (!extension_loaded("util")) {
    print "skip";
} ?>
--FILE--
<?php
Class Test {
    public $name;
    public $val;
    public function __construct($name, $value)
    {
        $this->name = $name;
        $this->val = $value;
    }
}

$arr = ['key' => ['val' => 'str'], 1 => ['val' => 2], ['val' => 3], new Test('harry', 1000), [1,2,3]];
var_dump(Util::array_pluck($arr, 'val'));
var_dump(Util::array_pluck($arr, 'val', false));
var_dump(Util::array_pluck($arr, 'val', true, false));
var_dump(Util::array_pluck($arr, 'val', false, false));
?>
--EXPECT--
array(4) {
  ["key"]=>
  string(3) "str"
  [1]=>
  int(2)
  [2]=>
  int(3)
  [3]=>
  int(1000)
}
array(4) {
  [0]=>
  string(3) "str"
  [1]=>
  int(2)
  [2]=>
  int(3)
  [3]=>
  int(1000)
}
array(5) {
  ["key"]=>
  string(3) "str"
  [1]=>
  int(2)
  [2]=>
  int(3)
  [3]=>
  int(1000)
  [4]=>
  array(3) {
    [0]=>
    int(1)
    [1]=>
    int(2)
    [2]=>
    int(3)
  }
}
array(5) {
  [0]=>
  string(3) "str"
  [1]=>
  int(2)
  [2]=>
  int(3)
  [3]=>
  int(1000)
  [4]=>
  array(3) {
    [0]=>
    int(1)
    [1]=>
    int(2)
    [2]=>
    int(3)
  }
}
