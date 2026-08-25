# Environnement de developpement TCH009 (optionnel).
# Ubuntu 24.04 + la chaine d'outils C utilisee dans le cours.
FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get install -y --no-install-recommends \
        build-essential \
        gcc \
        clang \
        cmake \
        ninja-build \
        gdb \
        valgrind \
        clang-format \
        clang-tidy \
        cppcheck \
        git \
        ca-certificates \
        locales \
    && sed -i '/fr_CA.UTF-8/s/^# //' /etc/locale.gen \
    && locale-gen \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

ENV LANG=fr_CA.UTF-8
