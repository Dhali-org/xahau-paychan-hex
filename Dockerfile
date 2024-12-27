FROM ubuntu:latest

# Set the working directory
WORKDIR /code

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential libssl-dev libboost-all-dev cmake libnode-dev libhowardhinnant-date-dev \
    && rm -rf /var/lib/apt/lists/*

COPY . /code/

RUN rm -rf build && mkdir build && cd build && cmake .. && cmake --build .

ENV PORT 80

EXPOSE 80

CMD ["node", "example.js"]
