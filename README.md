# README

## 環境

- OS Edition : Windows 11 Pro
- OS Version: 23H2
- Processor : 11th Gen Intel(R) Core(TM) i7-11800H @ 2.30GHz 2.30 GHz
- WSL : Ubuntu 22.04.3 LTS

```
sudo apt update -y && sudo apt upgrade -y
```

## 1

1. gcc, g++, make, gnuplotのインストール

```
sudo apt install -y gcc g++ make gnuplot gnuplot-x11
```

2. VcXsrv(Xサーバー)をWindowsにインストール

- ダウンロード︓https://sourceforge.net/projects/vcxsrv/
- 起動時に毎回「Disable access control」にチェックを⼊れる

3. 各種機能の動作確認

- ```~/.bashrc```の末尾に追記

```
export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):0
```

- コマンドラインで実行

```
source ~/.bashrc
gnuplot
plot sin(x)
```

4. LittleSLAMのインストール

```
sudo apt install -y build-essential cmake libboost-all-dev libeigen3-dev unzip
git clone --recursive https://github.com/furo-org/LittleSLAM.git
cd LittleSLAM
mkdir build && cd build
cmake ..
make
cd cui
sudo wget https://furo.org/software/little_slam/dataset.zip
mkdir dataset
unzip dataset.zip -d dataset
./LittleSLAM dataset/corridor.lsc
```

5. OpenCVのインストール

```
cd
sudo apt install -y libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo wget -O opencv.zip https://github.com/opencv/opencv/archive/4.7.0.zip
unzip opencv.zip
wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/4.x.zip
unzip opencv_contrib.zip
cd opencv-4.7.0
sudo mkdir build && cd build
sudo cmake .. -DOPENCV_EXTRA_MODULES_PATH=$HOME/opencv_contrib-4.x/modules -DCMAKE_INSTALL_PREFIX=/usr -DWITH_GK=ON
sudo make -j4
sudo make install
```

6. EPOS

```
unzip EPOS-Linux-Library-En-20240407.zip
cd EPOS_Linux_Library
sudo bash ./install.sh
```

7. Lidar

```
unzip YDLidar-SDK TG30-20240407.zip
cd YDLidar-SDK-master/build
sudo cmake ..
sudo make
sudo make install
```

8. depth

```
sudo apt install -y libatomic-ops-dev
```