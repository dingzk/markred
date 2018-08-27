make clean
./configure --with-php-config=/usr/local/php/bin/php-config CFLAGS='-std=c99' --enable-debug

make
make install
