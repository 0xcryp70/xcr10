# Base image for build stage
FROM ubuntu:22.04 AS builder

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Update base and install build tools
RUN apt-get update && apt-get install -y \
    curl wget git unzip python3 python3-pip jq software-properties-common \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install Networking tools
RUN apt-get update && apt-get install -y \
    tcpdump traceroute iputils-ping net-tools dnsutils iproute2 strace bpftrace \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install Database CLI tools
RUN apt-get update && apt-get install -y \
    postgresql-client redis-tools mysql-client rabbitmq-server \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install cqlsh via pip
RUN pip3 install cqlsh

# Install MongoDB Database Tools
RUN wget https://fastdl.mongodb.org/tools/db/mongodb-database-tools-ubuntu2204-x86_64-100.7.2.deb \
    && dpkg -i mongodb-database-tools-ubuntu2204-x86_64-100.7.2.deb \
    && rm mongodb-database-tools-ubuntu2204-x86_64-100.7.2.deb

# Runtime image
FROM ubuntu:22.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install base tools
RUN apt-get update && apt-get install -y \
    curl wget git python3 python3-pip nano vim \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Copy tools from build stage
COPY --from=builder /usr/local/bin/* /usr/local/bin/
COPY --from=builder /usr/ /usr/
COPY --from=builder /bin/ /bin/
COPY --from=builder /lib/ /lib/
COPY --from=builder /lib64/ /lib64/
COPY --from=builder /sbin/ /sbin/
# Set default command
CMD ["/bin/bash"]

