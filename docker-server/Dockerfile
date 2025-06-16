FROM ubuntu:22.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    qt5-qmake \
    qtbase5-dev \
    qtdeclarative5-dev \
    qttools5-dev \
    libsqlite3-dev \
    pkg-config \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .
RUN qmake server.pro && make -j$(nproc)

CMD ["./server"]