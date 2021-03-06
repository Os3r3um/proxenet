# Configuration

## Plugins

You will find plenty of working examples for creating your own plugins in the
`examples/` directory of the project. And if you feel like contribution your
scripts, feel free to
[submit them](https://github.com/hugsy/proxenet-plugins/pulls).

## SSL/TLS keys

SSL/TLS layer is fully built-in and extremely flexible thanks to the amazing [PolarSSL](http://polarssl.org/)
library. Version 1.3+ of the library must be installed to compile `proxenet`.

- Using your own SSL/TLS keys can be done easily with command line parameters
```
$ ./proxenet --key=/path/to/ssl.key --cert=/path/to/ssl.crt
```

- If you don't trust me (which is a good thing), you can re-generate new SSL/TLS keys easily:
```
$ make -C keys
```

## Proxy forwarding

`proxenet` can also seemlessly relay HTTP traffic and forward it to another HTTP proxy.

``` bash
$ ./proxenet -X 192.168.128.1 --proxy-port 3128
INFO: Starting interactive mode, press h for help
INFO: Infos:
- Listening interface: localhost/8008
- Supported IP version: IPv4
- Logging to stdout
- Running/Max threads: 0/10
- SSL private key: /home/hugsy/code/proxenet/keys/proxenet.key
- SSL certificate: /home/hugsy/code/proxenet/keys/proxenet.crt
- Proxy: 192.168.128.1 [3128]
- Plugins directory: /home/hugsy/code/proxenet/plugins
Plugins list:
|_ priority=1   id=1   type=Python    [0x0] name=DeleteEncoding       (ACTIVE)
|_ priority=2   id=2   type=Ruby      [0x1] name=InjectRequest        (ACTIVE)
|_ priority=2   id=3   type=Python    [0x0] name=InjectRequest        (ACTIVE)
|_ priority=9   id=4   type=Python    [0x0] name=Intercept            (ACTIVE)
```

`proxenet` also supports SOCKS4, and SOCKS4a proxy forwarding (useful when tunnelling through SSH).


## Daemon mode

Running as daemon will make `proxenet` detach from the current terminal session. This is very convenient when it is used on a shared host.

To do this, simply run an instance with the `-d` option.
```bash
$ ./proxenet -dv
WARNING: proxenet will now run as daemon
WARNING: Use `control-client.py' to interact with the process.
$
```

