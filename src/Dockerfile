FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    check \
    locales \
    && locale-gen en_US.UTF-8 \
    && apt-get clean

ENV LANGUAGE=en_US.UTF-8

WORKDIR /project
COPY . .

RUN if [ -f Makefile ]; then make; fi

CMD ["make", "test"]
