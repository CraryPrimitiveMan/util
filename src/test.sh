make clean
phpize
./configure
make
sudo make install
php util.php
export TEST_PHP_EXECUTABLE=/usr/bin/php
php run-tests.php tests/*
