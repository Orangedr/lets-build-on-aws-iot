#include <pgmspace.h>

#define SECRET
#define THINGNAME "ESP32"

const char WIFI_SSID[] = "Healthy Guest";
const char WIFI_PASSWORD[] = "Welcome2Healthy!";
const char AWS_IOT_ENDPOINT[] = "a2msm1jn7tex3i-ats.iot.us-west-2.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUPMhHRkoh+0LrynVfh0+mnAaomNkwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIyMDgwODIzMDA1
OFoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAOewQYiyKQAgd4b481sw
dnuObeRQ2fkpuoVMIJzJfZUdemaXQtOMM6q+BWR+7NVrjF48ox0a8hP8sDVUf+Kk
MD2B9OrEgodOg1ot59LaG6TKC972hpMeWw45v4AmGR8ghE6kaXggqq5QYCVI60o2
vVxYMQV5a6zPG4unULa+PjNBrB4qqrJcBsIko7GCc4C+utS848yVYuQtjRsok9t/
xEe2qt3vP7/He4R7X1zdcsji06qHxVsOHxqyGWFsFAmeyr6VBmSJxvUJzP4ZUtUN
yZ/xmF86r54vVFNd0myKn05KbgmQu9F1BuG8b2MnbhvZJUQdIsPm6nwxvwJfxFnu
i/MCAwEAAaNgMF4wHwYDVR0jBBgwFoAUKM1TloEXhTFA9aVpJulETPzrblowHQYD
VR0OBBYEFPdGqsSw0i+4jeu0Cf7R+jmyGmTrMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQAxspw7eQZa1pPGDJlyEAcUt9Z9
orqgyDGYbUEWG3C02zTiFWbxKgQ/Gf61MhVRR7hNEjEwmqhJThBMvmi2ZY7Ugih5
0ou/UWVxRp3opAEiGTGfMHFTegsmTD32xjqk7nMgWy309z9h7QtCQ9IHZkN+RyAg
uzHol4+FuthtW5IhJicsp+7BYVUFuIK9QgvdpD8C53a93L8u9T1VUaqglDp00JWM
3nTQaV1c2EF1tedYYNvaKLvrkuGJmQ7Hkd1JBE289KYIsq4AgUW5mC9ifcGV4f48
VjbKOnOl+DXXH31Pe09w6VaYRUUh/rF3wRt4drDjrn1EO3/nAlfyjkz8CfaB
-----END CERTIFICATE-----

)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA57BBiLIpACB3hvjzWzB2e45t5FDZ+Sm6hUwgnMl9lR16ZpdC
04wzqr4FZH7s1WuMXjyjHRryE/ywNVR/4qQwPYH06sSCh06DWi3n0tobpMoL3vaG
kx5bDjm/gCYZHyCETqRpeCCqrlBgJUjrSja9XFgxBXlrrM8bi6dQtr4+M0GsHiqq
slwGwiSjsYJzgL661LzjzJVi5C2NGyiT23/ER7aq3e8/v8d7hHtfXN1yyOLTqofF
Ww4fGrIZYWwUCZ7KvpUGZInG9QnM/hlS1Q3Jn/GYXzqvni9UU13SbIqfTkpuCZC7
0XUG4bxvYyduG9klRB0iw+bqfDG/Al/EWe6L8wIDAQABAoIBAHMC/vUxo8LJWyxo
Zr3Mx/Q71vdw31Od0FadXM8YArxEHt/QlL7ZKUjH/XtOupiTQ+H/7eTj3GnplTtU
EAvc/4l4+rCUDkvGwNPCWANGfFSIa+4pqNJdTkw4hITD5NKb3LIBUc3tQW04vxGj
KhH0LHor2WHjTX1CbmUcEKg2tj/QluiN0iB4Dnhx+XJwB3cQgpnpY0ikT+3bb33Y
DPjPc+tIq/kfO4E04l0MLHw9s8wx/HvVhlEQFXVTQgP/mE81IT5cYde//xfd/2u1
02Ai/T4Cni562mp/lsVwtaAPn0xeZeOQZdIpi4xdf8nIDGZtcHVv6RoM0gGUbMyL
4YnfQcECgYEA/wKZbkczd+UP/SuwaqPonYlLuTnon1Tje/Vy53J6gIGXXocE20i5
wfVBOvmJ9aAcwM8t7zzAnj5GVefYGhOsSFas/QKBfoWFpPVhchvCA6ynSL8cQyZR
wR4NhQ2uIjZRcDuE0AoYUqF3dKvONNzjKCCUC2KDB4dbQ78g7B4OwtMCgYEA6JZ7
cQsyAlYT514MD5b/8sSFe3soZWYTrJaHuGlU/K4gDzkfSFB+JtP5SD5TLoSZFukn
KMbiNNQC5EE/VfM6o+552KxXB1I+OxREluPRG/1A4e6IURbliUkJjVjG0pj4bkKV
TTsokRvuKwd8rfpSStRrGTzhApAQmzf4yXE2HmECgYAmARYqqDPUb2/VlDhDfFAD
gl2lqiqv7C/G3oqUUaxOEIIllUu0/n6omEtzZZMY5xbB6V54I/601qUW0mmTYVEw
qrI3NrNjzrRfJC60mcxtTcLUhZ7JpyFR/Y+YP7Su5pd2eXhOpOKBFg0+dwhROoYk
Cc7mb3UFnzeLviVC6yvZ/wKBgQCoKPyQy65ZgBCd7CI+N0dQJ4P2tiGLxlSdKKxx
yT4X/nDRcNRMPV4oBoQqFl2fuWDR7rpQQhMUbOC2VPJM2zFfirDv1hKKCY1Su6Gn
kokCeoUplINcVXiZXIQafMArTUv4tA0sLIR0/cOhuqULSHus/I1+TsTETJKlFr+6
LS8aoQKBgBGZ21hWTraee09l+yOZjKFJwRKWKyHOobRYrXGFgDHESwzKWjY653nB
0U2/vVsfDBhScf07yaTUbBf4n06gS4PQbQDHMq3HB2TCKgEDSTyIvMz7yJqRy5Hx
hykVBDMI5IKVN3C3M7jSdwfJObwuR1hIQUJ/A0kfxrh4tmygcHIr
-----END RSA PRIVATE KEY-----
)KEY";
