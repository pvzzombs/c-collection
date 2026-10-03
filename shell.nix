{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = with pkgs; [
    vim
    meson
    ninja
    gcc
  ];
}
