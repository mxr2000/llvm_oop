./main $1.llop
LLVM=/opt/homebrew/Cellar/llvm/16.0.0/bin
$LLVM/clang-16 -Woverride-module a.ll rt.ll -o $1 2> /dev/null
./$1 > a.txt
