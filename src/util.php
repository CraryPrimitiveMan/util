<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if (!extension_loaded('util')) {
    dl('util.' . PHP_SHLIB_SUFFIX);
}
$module = 'util';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach ($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
$function = 'confirm_' . $module . '_compiled';
if (extension_loaded($module)) {
    $str = $function($module);
} else {
    $str = "Module $module is not compiled into PHP";
}
echo "$str\n";
$arr = [1, 2 , 3];
echo 'Util::array_first($arr) === reset($arr) : ', Util::array_first($arr) === reset($arr), "\n";
echo 'Util::array_last($arr) === end($arr) : ', Util::array_last($arr) === end($arr), "\n";
