FROM nervos/ckb-riscv-gnu-toolchain:bionic
LABEL maintainer="Nervos Core Dev <dev@nervos.org>"

ADD http://www.lua.org/ftp/lua-5.1.5.tar.gz /opt/lua.tar.gz

# Build Lua VM
RUN mkdir -pv /opt/workdir && \
 tar xvf /opt/lua.tar.gz -C /opt/workdir/ && \
 cd /opt/workdir/lua-* && \
 make generic CC=riscv64-unknown-elf-gcc -j3 && \
 make install && \
 rm -rf /opt/lua.tar.xz /opt/workdir

WORKDIR /app
COPY ./ .
RUN riscv64-unknown-elf-gcc -I. -I./deps/ckb-c-stdlib/  -I/usr/local/include/ entry.c -o /opt/entry -L/usr/local/lib/ -llua -lm
