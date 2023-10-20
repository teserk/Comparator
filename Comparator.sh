#!/bin/bash

if [ ! -e ./build/bin/Comparator ]; then
  echo "/build/bin/Comparator не найден. Компилируем исходный код..."
  mkdir build
  cd build
  cmake -DBUILD_TESTS=OFF ..
  make
fi

if [ -e ./build/bin/Comparator ]; then
  ./build/bin/Comparator "$@"
else
  echo "Ошибка: не удалось найти или скомпилировать /build/bin/Comparator. Попробуйте удалить build и запустить заново."
fi

