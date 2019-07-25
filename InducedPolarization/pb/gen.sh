protoc -I=./ --cpp_out=./ ./Project.pb
find . -name "*.cc" -exec clang-format -i -style=file {} \;
find . -name "*.h" -exec clang-format -i -style=file {} \;