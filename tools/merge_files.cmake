# Kreuzstich
# Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

separate_arguments(INPUT_LIST NATIVE_COMMAND "${INPUT}")
file(WRITE "${OUTPUT}" "")
foreach(ITEM IN LISTS INPUT_LIST)
    file(READ "${SOURCE_DIR}/${ITEM}" FILE_CONTENT)
    file(APPEND "${OUTPUT}" "${FILE_CONTENT}")
endforeach()
