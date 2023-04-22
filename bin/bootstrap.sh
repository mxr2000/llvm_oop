declare -r ANTLR_VERSION=4
declare -r JAVA_VERSION=11
declare -r LLVM_VERSION=16


bootstrap_mac_env() {
  echo export LLVM_DIR=$(brew --prefix llvm@$LLVM_VERSION)/lib/cmake >> ~/.bashrc
  echo export LLOPCLANG=$(brew --prefix llvm@$LLVM_VERSION)/bin/clang >> ~/.bashrc
}


bootstrap_mac_dependencies() {
  if ! [ -x "$(command -v brew)" ]; then
    echoerr error: Homebrew is not installed.
    exit 1
  fi

  brew install homebrew/cask-versions/corretto$JAVA_VERSION
  brew install \
    git \
    cmake \
    pkg-config \
    llvm@$LLVM_VERSION \
    antlr@$ANTLR_VERSION
}


bootstrap_mac() {
  bootstrap_mac_dependencies
  bootstrap_mac_env
}


bootstrap() {
  bootstrap_mac

  echogreen
  echogreen '--------------------------------------------------------------------------------'
  echogreen '* bashrc has been updated - be sure to source the file or restart your shell.  *'
  echogreen '--------------------------------------------------------------------------------'
}

bootstrap