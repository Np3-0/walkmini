# Walk-Mini
A customizable, portable music player created for Hack Club: Fallout.

## About Walk-Mini
Music is one of the only genres that can connect people who believe in different topics, live in different areas, and who even speak different languages. However, it is becoming harder to listen to it, without shelling out 10 dollars a month, or buying a vinyl (which nobody will carry around). <br> People already carry around old IPods and other technology like this, so I wanted to make my own spin on it.

## Key Features
* Fully customizable theming
  - Users can print their own cases and choose between a wide range of themes for the firmware.
* Bluetooth, Headphone Jack, and Speaker support!
* 2.4 Inch TFT display with vibrant colors!
* Unlimited Song Storage!
  - Depends on SD size.
* And More!

## How to Use
1. Put in **4 AA Batteries**.
2. It should start up automatically!
   - I would recommend taking batteries out when not in use, in order to save power.
<br>
On the main page, there are six options (characterized with icons): Restart, Pause/Resume, Skip, Songs, Shuffle, and Settings.
<br>The settings page contains Customize, Bluetooth, and Contributions.

## BOM
| Part Name      | Description | Quantity | Unit Price | Total Price | URL | Running Total |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| ESP32-WROOM-32E-N4 | MCU | 1 | $3.22 | $3.22 | [AliExpress](https://www.aliexpress.us/item/3256806057158706.html?utparam-url=scene%3Asearch%7Cquery_from%3Apc_back_same_best%7Cx_object_id%3A1005006243473458%7C_p_origin_prod%3A&algo_pvid=df30c4ff-dec8-4a3b-af10-f2fe7d864fab&algo_exp_id=df30c4ff-dec8-4a3b-af10-f2fe7d864fab&pdp_ext_f=%7B%22order%22%3A%22237%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.29%210.99%21%21%213.29%210.99%21%402103122117772588423246279e2c68%2112000052254647571%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A73118c74%3Bm03_new_user%3A-29895%3BpisId%3A5000000203712600&gatewayAdapt=4itemAdapt) | $3.22
| CP2102-GMR | USB to UART | 1 | $0.80 | $0.80 | [AliBaba](https://www.alibaba.com/product-detail/New-and-Original-CP2102-GMR-Electronic_1601731751516.html?priceId=cb0ce5b769d94795981c469bdce9a953) | $4.02
| SD-6-B | SD Card Reader | 1 | $0.58[^1] | $0.58 | [Same Sky](https://www.sameskydevices.com/product/interconnect/connectors/memory-card-connectors/sd-card-connectors/sd-6-b?srsltid=AfmBOoril4IXa0zYMeqRdO9H5vuY9dfO0f5PHj1uIutQLSDhJAolr3nc) | $4.60
| 1825910-6 | 6mm Button | 6[^2] | $0.057 | 1.14 | [AliExpress](https://www.aliexpress.us/item/3256805658758223.html?algo_pvid=5b5d2596-e29a-46b4-bfae-5d09a7e446dd&algo_exp_id=5b5d2596-e29a-46b4-bfae-5d09a7e446dd-16&pdp_ext_f=%7B%22order%22%3A%223214%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%211.09%210.99%21%21%211.09%210.99%21%402101e2b017785468262657316ef6b8%2112000034553364519%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A1ae5c6f1%3Bm03_new_user%3A-29895%3BpisId%3A5000000203537363&curPageLogUid=a4N1OIlqDFoz&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005005845072975%7C_p_origin_prod%3A) | $5.74
| PCM5102APWR | Audio Jack Controller | 1 | $1.00 | $1.00 | [AliBaba](https://www.alibaba.com/product-detail/PCM5102APWR-IC-Chip-20-TSSOP-Brand_1600511085959.html?priceId=ba42e2395af34fafaf9c4b6be956c1c8) | 6.74 
| MAX98357AETE+T | Speaker Controller | 1 | $0.10 | $0.10 | [AliBaba](https://www.alibaba.com/product-detail/New-and-Original-MAX98357AETE-T-Electronic_1601732000471.html?priceId=2ccbc724114a490fb1ee81e4e230e6b8) | 6.84
| SJ-3523-SMT-TR | Headphone Jack | 1 | $0.88 | $0.88 | [DigiKey](https://www.digikey.com/en/products/detail/same-sky-formerly-cui-devices/SJ-3523-SMT-TR/281297) | $7.72
| AI-4328-P-C120D-R | Speaker | 1 | $16.92 | $16.92 | [DigiKey](https://www.digikey.com/en/products/detail/pui-audio-inc/ai-4328-p-c120d-r/1738481) | $24.64
| 2477 | Battery Holder | 1 | $1.87 | $1.87 | [Digikey](https://www.digikey.com/en/products/detail/keystone-electronics/2477/303822) | $26.51
| MCP1826S-3302E/AB | LDO | 1 | $0.66 | $0.66 | [AliBaba](https://www.alibaba.com/product-detail/Electronic-Circuit-Components-MCP1826S-3302E-AB_1601731375638.html?priceId=8291b1507dca417ca7b029191e1e88de) | $27.17
| USB4085-GF-A | USB-C Connector | 1 | $0.04 | $0.04 | [AliBaba](https://www.alibaba.com/product-detail/Hainayu-BOM-capacitor-resistance-table-quotation_1601270438701.html?priceId=a70c80eafee34aba80d3bcf18a5baf0e) | $27.21
| 1N5819 | Schottky Diode | 1 | $0.01 | $0.01 | [AliBaba](https://www.alibaba.com/product-detail/Through-hole-Schottky-Diodes-1N5817-1N5818_1601557699434.html?selectedCarrierCode=SEMI_MANAGED_STANDARD%40%40STANDARD&priceId=6f243cc781264e41885941c826333b64) | $27.22
| 0530471410 | Display 14 Pin Connector | 1 | $0.81 | $0.81 | [DigiKey](https://www.digikey.com/en/products/detail/molex/0530471410/259377) | $28.03
| ILI9341 | 2.4 Inch TFT Display | 1 | $5.16 | $5.16 | [AliExpress](https://www.aliexpress.us/item/3256803732365701.html?algo_pvid=335efabf-7043-43e3-b1e5-88cb6faf5a31&algo_exp_id=335efabf-7043-43e3-b1e5-88cb6faf5a31-15&pdp_ext_f=%7B%22order%22%3A%22208%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%214.45%211.78%21%21%214.45%211.78%21%402103128917785486140741950e4710%2112000056542062912%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A46ae3b9e%3Bm03_new_user%3A-29895%3BpisId%3A5000000204886261&curPageLogUid=W4D3fCRCIHOw&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005003918680453%7C_p_origin_prod%3A) | $33.19
| PCB | JLCPCB for project | 5 | $1.64 | $8.20 | [JLCPCB](https://jlcpcb.com/) | $41.39
| ABS07-32.768KHZ-T | 32.768 Khz Crsytal | 1 | $0.61 | $0.61 | [Digikey](https://www.digikey.com/en/products/detail/abracon-llc/ABS07-32-768KHZ-T/1236858) | $42.00
| MBA02040C3003FC100 | 300K Ohm Resistor | 1 | $0.66 | $0.66 | [Digikey](https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MBA02040C3003FC100/7350347) | $42.66
| MBA02040C1002FRP00 | 10K Ohm Resistor | 10 | $0.095 | $0.95 | [Digikey](https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MBA02040C1002FRP00/336349) | $43.61
| MBA02040Z0000ZCT00 | 0 Ohm Resistor | 2 | $0.14 | $0.28 | [Digikey](https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MBA02040Z0000ZCT00/5066485) | $43.89
| MBA02040C5104FC100 | 5M Ohm Resistor | 1 | $0.39 | $0.39 | [Digikey](https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MBA02040C5104FC100/5059352?s=N4IgjCBcoCwGxVAYygMwIYBsDOBTANCAPZQDaIA7BQJwQC6hADgC5QgDKzATgJYB2AcxABfQgCYADAA4ArIhApIGHAWJkQMgHRgABAFkA8gAsAtthAMQLNgFU%2BPZgdR7c6bAFcuuEYQC0Y%2BUVud1USSHI5OmFREADwkC9sHmxmIi5zKKA) | $44.28
| MBA02040C4707JC100 | 470 Ohm Resistor | 2 | $0.49 | $0.98 | [Digikey](https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MBA02040C4707JC100/5059320?s=N4IgjCBcoCwGxVAYygMwIYBsDOBTANCAPZQDaIA7BQJwQC6hADgC5QgDKzATgJYB2AcxABfQgCYADAA4ArIhApIGHAWJkQMChIAEAWwDyAC13YQDECzYBVPj2b7UAWVzpsAVy64RhALRj5itxuqiSQ5HJ0wqIg-mEgntg82MxEXKaRQA) | $45.26
| MBA02040C5101FRP00 | 5.1K Ohm Resistor | 2 | $0.11 | $0.22 | [Digikey](https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MBA02040C5101FRP00/333758) | $45.48
| MBA02040C2209FCT00 | 22 Ohm Resistor | 2 | $0.21 | $0.42 | [Digikey](https://www.digikey.com/en/products/detail/vishay-beyschlag-draloric-bc-components/MBA02040C2209FCT00/5062426) | $45.90
| FK14X5R0J226MR020 | 22 µF Capacitor | 2 | $0.50 | $1.00 | [Digikey](https://www.digikey.com/en/products/detail/tdk/FK14X5R0J226MR020/2815215) | $46.90
| FK14X7R2A104KN020 | 0.1 µF Capacitor | 10 | $0.253 | $2.53 | [Digikey](https://www.digikey.com/en/products/detail/tdk/FK14X7R2A104KN020/2815243) | $49.43
| FG18C0G1H120JNT06 | 12pF Capacitor | 2 | $0.22 | $0.44 | [Digikey](https://www.digikey.com/en/products/detail/tdk/FG18C0G1H120JNT06/5802787) | $49.87
| FG18X7R1A225KRT06 | 2.2 µF Capacitor | 4 | $0.32 | $1.28 | [Digikey](https://www.digikey.com/en/products/detail/tdk/FG18X7R1A225KRT06/5802874) | $51.15
| FK18X5R0J105KN020 | 1 µF Capacitor | 2 | $0.28 | $0.56 | [Digikey](https://www.digikey.com/en/products/detail/tdk/FK18X5R0J105KN020/2815325) | $51.71
| FK18X5R1A475KR020 | 4.7 µF Capacitor | 1 | $0.34 | $0.34 | [Digikey](https://www.digikey.com/en/products/detail/tdk/FK18X5R1A475KR020/2815334) | $52.05
| ECE-A1EKA100I | 10 µF Polarized Capacitor | 5 | $0.26 | $1.30 | [Digikey](https://www.digikey.com/en/products/detail/panasonic-industry/ECE-A1EKA100I/2689086) | $53.35


**Enjoy!**
---
Made with love by Np3 (nate), 17, NJ

[^1]: Price is assumed for one SD-reader. For multiple, go [here:](https://www.alibaba.com/product-detail/Brand-New-Original-CONN-SD-CARD_1601485307544.html?priceId=8b2470e5a66946c49b35714d15eefd60)
[^2]: Button comes in package of 20.

Shield: [![CC BY-NC-ND 4.0][cc-by-nc-nd-shield]][cc-by-nc-nd]

# License
This work is licensed under a
[Creative Commons Attribution-NonCommercial-NoDerivs 4.0 International License][cc-by-nc-nd].

[![CC BY-NC-ND 4.0][cc-by-nc-nd-image]][cc-by-nc-nd]

[cc-by-nc-nd]: http://creativecommons.org/licenses/by-nc-nd/4.0/
[cc-by-nc-nd-image]: https://licensebuttons.net/l/by-nc-nd/4.0/88x31.png
[cc-by-nc-nd-shield]: https://img.shields.io/badge/License-CC%20BY--NC--ND%204.0-lightgrey.svg
