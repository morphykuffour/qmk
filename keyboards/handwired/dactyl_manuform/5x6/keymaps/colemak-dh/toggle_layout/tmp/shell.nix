with import <nixpkgs> {};
stdenv.mkDerivation {
  name = "toggle_layout";
  buildInputs = [ hidapi ];
buildPhase = ''
  NIX_CFLAGS_COMPILE="$(pkg-config --cflags hidapi) $NIX_CFLAGS_COMPILE"
  # put the usual make/gcc code here
'';
}
