##     ECO PLAST STM32F401    ##

=> PROJE HEDEF :

*  Ürün verilerinin alınması ve bu verilerin MQTT üzerinden yazılıma ulaştırılması.
Süreç içerisinde veriler SD kart üzerinden yönetilecek. Thermocouple verileri 
bir sonraki aşama için düşünülüyor. 

**Yapılacaklar:** 

* Veri sd kart üzerinden taşınacak.
* Veri mqtt ile aktarılacak. (Rabitmq)
* Veri kayıplarını önlemek amacıyla koda linked-list yapısı eklenecek. Sistem sd üzerinden akacak. Eğer o an sd error verirse
veri kaybını önlemek amacıyla linked listte tutulacak ve sd tekrar ayağa kalkana kadar süreç bu şekilde devam edecek. 

**NOTLAR ve KARŞILAŞILAN SORUNLAR:**

* Kart 24V ile beslenirken Uart TLL veya STLink ile debug sorun yaratıyor. 
* NTP bazen yanıt vermiyor. Delay kullanıldıktan sonra başarılı oldu ancak tekrar tekrar denenmedi. [Çözüldü]
* Sinyal süreleri farklı olabiliyor. Bazıları çok hızlı, inputCheck timer hızlandırılınca sorun çözüldü.


	13.09.2022 SAHA ÇALIŞMASI NOTLARI:

- NTP SUNUCU İÇİN ETHNETNET GEREKLİ. Bu deneme elle static olarak saat tarih atanarak yapıldı.
- SİNYAL SÜRELERİ EXCELL TABLOSUNDAN FARKLI.
- Çalışma başarılı oldu veriler eksiksiz sd karta yazıldı. 
- Çok hızlı input okunmalı. Üründen ürüne vs sinyal süreleri değişiyor.

19.10.2022 SAHA NOTLARI:

- Klemenslerdeki kablo bağlantılarını kontrol et. Sahadaki şartlardan dolayı eksik veya hatalı yapılmış olunabilir. Sorunlar yaratabiliyor.
- Sahaya kart götürmeden önce donanımsal test yap.   