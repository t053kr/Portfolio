# Wireless potentiometer with Netshield
Documentation is for Arduino <-> Unreal Engine project

This project connects physical world into virtual world wirelessly. In this project a player can send a command wirelessly to Arduino. When a player press keyboard number 1 it will give controls to Arduino potentiometer to adjust a light in the game. When a player press x on keyboard it will disconnect the connection.

Data transfer between Arduino and computer is made wirelessly in WiFi network. To do this, [Sparkfun ESP8266 WiFi shield](https://www.sparkfun.com/products/13287) and a plugin for TCP communication is needed. This demo uses payed [Netshield](https://www.unrealengine.com/marketplace/en-US/product/netshield) plugin and [Unreal Engine 4.25.4](https://www.unrealengine.com/en-US/)

_Note: Signal between UE and Arduino varies a lot. It is sometimes needed to send multiple commands before one is received by the other end. This happens also with Sparkfun ESP8266 Shield Demo so I came to conclusion that the reason is hardware related_

### This project is based in [Wireless potentiometer](https://github.com/HAMK-ICT-Project8/arduino-scripts/tree/main/Socketer/Wireless%20Potentiometer) so the setup and usage is almost identical. Follow instructions listed in that project and all you need to do is replace .uasset & .umap files.