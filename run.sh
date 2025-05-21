CC=gcc

$CC -o out/main.exe library/*.c -Iinclude

# -Wall -Wextra untuk ngecheck warning

if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./out/main.exe
else
    echo "Compilation failed."
fi