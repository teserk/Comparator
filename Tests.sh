#!/bin/bash

if [ ! -e ./build/bin/Tests ]; then
  echo "/bin/Tests не найден. Компилируем исходный код..."
  mkdir build
  cd build
  cmake -DBUILD_TESTS=ON ..
  make
fi

if [ -e ./build/bin/Tests ]; then
  ./build/bin/Tests
else
  echo "Ошибка: не удалось найти или скомпилировать /build/bin/Tests. Попробуйте удалить build и запустить заново."
fi

