# Base image for build stage
FROM ubuntu:22.04 AS builder

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Update base and install build tools
RUN apt-get update && apt-get install -y \
    curl wget git gcc make build-essential unzip python3 python3-pip jq yq software-properties-common \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install Kubernetes tools
RUN curl -LO "https://storage.googleapis.com/kubernetes-release/release/$(curl -s https://storage.googleapis.com/kubernetes-release/release/stable.txt)/bin/linux/amd64/kubectl" \
    && chmod +x kubectl && mv kubectl /usr/local/bin/ \
    && curl -fsSL https://raw.githubusercontent.com/helm/helm/main/scripts/get-helm-3 | bash \
    && curl -LO https://github.com/derailed/k9s/releases/latest/download/k9s_Linux_x86_64.tar.gz \
    && tar -xzf k9s_Linux_x86_64.tar.gz && mv k9s /usr/local/bin/ \
    && rm -rf k9s_Linux_x86_64.tar.gz \
    && curl -LO https://github.com/wercker/stern/releases/latest/download/stern_linux_amd64 \
    && chmod +x stern_linux_amd64 && mv stern_linux_amd64 /usr/local/bin/stern

# Install Networking tools
RUN apt-get update && apt-get install -y \
    tcpdump traceroute iputils-ping net-tools dnsutils iproute2 strace bpftrace \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install Database CLI tools
RUN apt-get update && apt-get install -y \
    postgresql-client redis-tools mysql-client mongodb-clients cqlsh rabbitmq-server \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Install CI/CD tools
RUN curl -LO https://github.com/kubernetes-sigs/kind/releases/latest/download/kind-linux-amd64 \
    && chmod +x kind-linux-amd64 && mv kind-linux-amd64 /usr/local/bin/kind \
    && curl -fsSL https://get.helm.sh/helm-v3.12.0-linux-amd64.tar.gz | tar xz && mv linux-amd64/helm /usr/local/bin/ \
    && apt-get install -y skopeo

# Runtime image
FROM ubuntu:22.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Install base tools
RUN apt-get update && apt-get install -y \
    curl wget jq yq git python3 python3-pip nano vim \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Copy tools from build stage
COPY --from=builder /usr/local/bin/* /usr/local/bin/

# Install other utilities
RUN pip install awscli

# Set default command
CMD ["/bin/bash"]
