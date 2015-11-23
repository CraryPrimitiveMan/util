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
}

$arr = ['a' => 10, 'b' => ['c' => 18, 'd' => 25, 30], 45];

$test1 = Util::array_map_deep($arr, function ($value) {
    return 'cool ' . $value;
});
$obj = new Man('harry');
$test2 = Util::array_map_deep($arr, [$obj, 'age']);
var_dump($test1);
var_dump($test2);
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
