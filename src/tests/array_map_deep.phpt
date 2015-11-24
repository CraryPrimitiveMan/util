--TEST--
Check for util array_map_deep
--SKIPIF--
<?php if (!extension_loaded("util")) {
    print "skip";
} ?>
--FILE--
<?php
class Man
{
    public $name;
    public function __construct($name)
    {
        $this->name = $name;
    }

    public function age($age)
    {
        return $this->name . ' ' . $age;
    }

    public function __toString()
    {
        return 'man, name is ' . $this->name;
    }
}

$obj = new Man('harry');
$arr = ['a' => 10, 'b' => ['c' => 18, 'd' => 25, 30], 45, 'obj' => $obj];

$test1 = Util::array_map_deep($arr, function ($value) {
    return 'cool ' . $value;
});
$test2 = Util::array_map_deep($arr, [$obj, 'age']);
$test3 = Util::array_map_deep($arr, function ($value) {
    return 'cool ' . $value;
}, true);
var_dump($test1);
var_dump($test2);
var_dump($test3);
?>
--EXPECT--
array(3) {
  ["a"]=>
  string(7) "cool 10"
  ["b"]=>
  array(3) {
    ["c"]=>
    string(7) "cool 18"
    ["d"]=>
    string(7) "cool 25"
    [0]=>
    string(7) "cool 30"
  }
  [0]=>
  string(7) "cool 45"
}
array(3) {
  ["a"]=>
  string(8) "harry 10"
  ["b"]=>
  array(3) {
    ["c"]=>
    string(8) "harry 18"
    ["d"]=>
    string(8) "harry 25"
    [0]=>
    string(8) "harry 30"
  }
  [0]=>
  string(8) "harry 45"
}
array(4) {
  ["a"]=>
  string(7) "cool 10"
  ["b"]=>
  array(3) {
    ["c"]=>
    string(7) "cool 18"
    ["d"]=>
    string(7) "cool 25"
    [0]=>
    string(7) "cool 30"
  }
  [0]=>
  string(7) "cool 45"
  ["obj"]=>
  string(23) "cool man, name is harry"
}
