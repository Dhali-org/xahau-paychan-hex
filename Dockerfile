FROM python:3.10

# Set the working directory
WORKDIR /code

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential libssl-dev libboost-all-dev cmake libnode-dev libhowardhinnant-date-dev pybind11-dev curl \
    && curl -sS https://bootstrap.pypa.io/get-pip.py | python3 \
    && rm -rf /var/lib/apt/lists/*


RUN pip install --no-cache-dir pybind11

COPY . /code/

RUN rm -rf build && mkdir build && cd build && cmake .. && cmake --build .

ENV PORT 80

EXPOSE 80

CMD ["node", "example.js"]
