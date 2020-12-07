FROM quay.io/pypa/manylinux2010_x86_64:latest AS env

RUN yum -y update \
&& yum -y install \
 autoconf \
 curl wget \
 gawk \
 gcc-c++ \
 git \
 libtool \
 make \
 openssl-devel \
 patch \
 pcre-devel \
 redhat-lsb \
 subversion \
 which \
 zlib-devel \
 unzip zip \
&& yum clean all \
&& rm -rf /var/cache/yum

# Install CMake 3.18.1
RUN wget "https://cmake.org/files/v3.18/cmake-3.18.1-Linux-x86_64.sh" \
&& chmod a+x cmake-3.18.1-Linux-x86_64.sh \
&& ./cmake-3.18.1-Linux-x86_64.sh --prefix=/usr --skip-license \
&& rm cmake-3.18.1-Linux-x86_64.sh

# Install Swig 4.0.2
RUN curl --location-trusted \
 --remote-name "https://downloads.sourceforge.net/project/swig/swig/swig-4.0.2/swig-4.0.2.tar.gz" \
 -o swig-4.0.2.tar.gz \
&& tar xvf swig-4.0.2.tar.gz \
&& rm swig-4.0.2.tar.gz \
&& cd swig-4.0.2 \
&& ./configure --prefix=/usr \
&& make -j 4 \
&& make install \
&& cd .. \
&& rm -rf swig-4.0.2