FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    check \
    && apt-get clean

WORKDIR /project
COPY . .

RUN if [ -f Makefile ]; then make; fi

CMD ["make", "test"]
