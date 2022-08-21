{ pkgs ? import <nixpkgs> { } }:

let
  dependencies = with pkgs; [
    libusb1
    hidapi
  ];
in
with pkgs;
mkShell {
  dependencies = dependencies;
  nativeBuildInputs = [
    pkg-config
  ];

  buildInputs = [
    dependencies;
  ];

}
