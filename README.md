# IoTCookBot
Buzdolabı Malzemelerine Göre Tarif Öneren IoT Destekli CookBot 
Problemin Tanımı 
Teknolojik yeniliklerden faydalanarak mutfak deneyimini iyileştirme amacı doğrultusunda yapılan bu 
proje, aşağıdaki problemlere çözüm olabilmektedir: 
♦ Yemek İsrafını Azaltma: Kullanıcıların buzdolabında bulunan malzemeleri kullanarak yemek 
yapmalarını sağlayarak israfı azaltır. 
♦ Kişisel Asistanlar: Kullanıcıların günlük yaşamla ilgili sorunlarına çözüm üretmektedir. 
♦ Ev Otomasyonu: Evdeki malzeme verilerini izleyerek kullanıcıların yemek yapma süreçlerini 
optimize edebilir. Aynı zamanda sistem, çevresel sıcaklık bilgisine sahip olduğu için yemek 
pişirme süreçlerinde rehberlik eder ve enerji verimliliği sağlar. 
♦ Yapay Zeka ve İnsan Etkileşimi: Kullanıcının malzeme girişiyle yapay zeka tabanlı tarif 
önerilerinde bulunabilir ve geri bildirimlerini alarak daha geniş bir insan-makine etkileşimi 
sağlayabilir.  
♦ Konfor ve İklimlendirme Kontrolü: Belirli bir sıcaklık aralığında gıdaların saklanması ve 
tazeliğinin korunması için önerilerde bulunabilir. 

Önerilen Çözüm 
♦ ESP8266 modülü, Adafruit IoT platformu ve OpenAI API entegrasyonu malzeme bilgilerinin 
sistematik bir şekilde işlenmesini sağlayarak sanal asistan fonksiyonlarını gerçekleştirmektedir. 
ESP8266 cihazı üzerinde MQTT protokolünü kullanarak, manuel olarak girilen malzeme verilerini 
ve sıcaklık sensöründen okunan değerleri Adafruit IO platformuna yayınlamakta ve buradan gelen 
komutlarla OpenAI API’ye istek yapmaktadır. Aynı zamanda, Adafruit IO'dan gelen buton 
durumunu dinlemekte ve belirli şartlar altında OpenAI'nin GPT-4 modelini kullanarak metin 
tabanlı cevaplar almaktadır. API, malzeme listesini ve sensörden okunan sıcaklık değerini analiz 
ederek uygun tarifler (sıcak havalarda hafif yemekler veya soğuk havalarda sıcak çorbalar gibi) 
oluşturur. Bu tarifler MQTT protokolü kullanılarak LCD ekranda adım adım görüntülenir.  
♦ Sistem yalnızca yemek tarifi önerilerinde bulunduğu için kullanıcı deneyimi daha odaklı ve 
verimli olur. Sistem, amacı doğrultusunda sıcaklık verilerini ve girilen malzemeleri analiz ederek 
kullanıcıya tarif önerileri dışında önerilerde bulunamaz. Modelin ince ayar (fine-tuning) yapılması 
ile tarif önerileri daha spesifik bir alana (örneğin yalnızca Türk mutfağına veya sağlıklı yemek 
tariflerine) odaklanabilir. Projeye başka işlevler eklemek istenirse (örneğin mutfak ipuçları verme, 
yemek planlaması yapma) modelin bu tür talepleri de karşılayacak şekilde tekrar eğitilmesi veya 
yapılandırılması faydalı olacaktır. 

Ekipman Listesi ve Kullanılan Teknolojiler 
♦ Esp8266 modülüne sahip Ardunio Modül (NodeMcu): Projeye internet bağlantısı sağlayarak 
OpenAI API ile iletişim kurar ve malzeme verilerini Adafruit IO platformuna iletir. 
♦ BreadBoard: Tüm bileşenlerin bağlantısını sağlamak için bir platform sunar. 
♦ Jumper Kablo: Elektriksel bağlantıları yapmak için kullanılır. 
♦ Direnç: Elektronik devrelerdeki akımı sınırlamak ve cihazların güvenli bir şekilde çalışmasını sağlar. 
♦ Buton: Kullanıcının tarife başlaması veya adımları geçmesi için bir girdi sağlar. 
♦ LCD Ekran: Tarif adımlarını ve malzeme bilgilerini görüntülemek için kullanılır. 
♦ Sıcaklık Sensörü (LM35): Sisteme çevresel sıcaklık bilgisi sağlayarak yemek pişirme süreçlerinde 
rehberlik eder ve enerji verimliliği sağlar. 
♦ Adafruit IoT Platformu: Malzeme bilgilerinin bulut ortamında saklanması ve MQTT protokolü ile 
işlenmesi için kullanılır. 
♦ MQTT Protokolü: IoT cihazları arasında hızlı ve güvenilir veri iletimi sağlar. 
♦ Ardunio Entegre Geliştirme Ortamı (IDE): ESP8266 programlama ve sistem testi için geliştirme 
ortamı olarak kullanılır. 
♦ OpenAI API: Kullanıcının malzeme listesinden ve sıcaklık değerinden yola çıkarak uygun yemek 
tarifleri oluşturur.

Maliyet, Enerji vb Analizler 
♦ Donanım Maliyetleri: Sensörler, mikrodenetleyiciler, ekranlar ve iletişim modülleri gibi donanım 
unsurları maliyetin önemli bir parçasıdır. Düşük güç tüketimi olan ve uygun fiyatlı donanımlar 
seçerek maliyeti düşürülebilir. 
♦ İnternet Bağlantısı ve Veri Aktarımı: Uygulamanın sürekli olarak internete bağlanması ve veri 
transferi enerji tüketimini artırabilir. Bu maliyet, kullanılan veri miktarına ve hizmet sağlayıcıya 
bağlı olarak değişebilir. 
♦ Güç Kaynakları: Pil veya elektrik kaynakları, uygulamanın sürekli çalışmasını sağlamak için 
gereklidir. Pil ömrü, pil kapasitesi ve pilin yeniden şarj edilebilir olup olmamasına göre maliyeti 
etkiler. 
♦ Enerji Tasarrufu ve Ekonomik Faydalar: Kullanılan IoT cihazlarının düşük enerji tüketimi 
sayesinde günlük enerji maliyetleri minimize edilerek enerji verimliliği sağlanır. Sistem, 
kullanıcı başına düşük bir maliyetle üretildiği için pazar standardına göre rekabetçi konumdadır. 
♦ Yazılım ve Geliştirme Maliyetleri: Yazılım geliştirme süreci, zaman ve kaynak gerektirir. 
Geliştirme araçları, lisanslar veya dış kaynak kullanımı gibi faktörler maliyeti etkileyebilir. 
Maliyetler, optimize edilen API kullanım stratejileri ile kontrol altına alınmıştır. 
♦ Veri İşleme ve Depolama: Bulut depolama veya sunucu hizmetleri kullanımı, verilerin 
saklanması ve işlenmesi için maliyeti artırabilir. 
♦ Bakım ve Destek: Uygulamanın sürekli olarak çalışabilirliği için bakım ve destek 
gerekebilir. Bu da maliyeti etkileyebilir. 
♦ Enerji Tüketimi ve İşletme Maliyetleri: Donanımın sürekli çalışması enerji tüketimine neden 
olur. Bu da işletme maliyetlerini oluşturur. Mevcut tarif uygulamalarının abonelik modellerine 
göre daha uygun maliyetli bir IoT çözümü sunar. 
Bu unsurların belirlenmesi ve analizi için bazı adımlar şunlar olabilir: 
♦ Donanım Seçimi: Düşük güç tüketimine sahip ve uygun fiyatlı donanımların seçilmesi. 
♦ Enerji Profil Analizi: Donanım bileşenlerinin ne kadar enerji tükettiğini belirlemek için bir 
enerji profil analizi yapılması. 
♦ Veri Aktarımı Optimizasyonu: Gereksiz veri transferlerini ve sık bağlantıları azaltarak enerji 
tüketimini ve maliyetleri düşürmek. 
♦ Bütçe ve Maliyet Planlaması: Donanım, iletişim, yazılım ve destek maliyetlerini planlamak 
için bütçe oluşturulması.

Büyük Veri Kapsamında Proje Nasıl Gerçekleştirilebilir? Hangi Teknolojiler 
Nasıl Kullanılabilir? 
♦ Veri Toplama ve Depolama: 
 Sensörler ve akıllı cihazlar aracılığıyla veri toplanır. Raspberry Pi, Arduino gibi 
platformlar ve uygun sensörler kullanılabilir. 
 Büyük veriyi depolamak için ölçeklenebilir veri tabanları kullanılabilir. Örneğin 
MongoDB, Cassandra, Elasticsearch gibi NoSQL veri tabanları. 
♦ Veri İşleme ve Analiz: 
 Kültürel yemek tercihlerini anlamak için kullanılabilir. 
 Büyük veri kümelerini işlemek için Apache Hadoop'un kullanılabilir. MapReduce, HDFS, 
ve diğer bileşenler büyük veri analizi için güçlü araçlar sunar. 
 Apache Kafka, veri akışlarını yönetmek için kullanılabilir. 
 Apache Spark, hızlı ve genel amaçlı bir veri işleme çerçevesidir. Büyük veri setlerini paralel 
işlemek için kullanılabilir.  
 Grafiksel olarak veri analizi için veri görselleştirme araçları kullanılabilir. Örneğin, 
Tableau, Power BI veya Python'daki Matplotlib, Seaborn gibi kütüphaneler. 
♦ Makine Öğrenimi ve Yapay Zeka: 
 TensorFlow veya PyTorch, derin öğrenme ve yapay zeka modelleri oluşturmak için 
kullanılabilir. 
 Scikit-learn, makine öğrenimi modellerini geliştirmek için kullanışlı bir kütüphanedir. 
♦ Veri Güvenliği ve Gizliliği: 
 Blockchain teknolojisi, veri güvenliği ve takibini sağlamak için kullanılabilir. 
 Veri şifreleme (AES veya TLS protokolleri), erişim kontrolü ve yetkilendirme araçları 
kullanılabilir. Örneğin OAuth protokolü. 
♦ Bulut Hizmetleri: 
 Büyük veri işleme, depolama ve analiz için bulut hizmetleri olan Amazon Web Services 
(AWS) Lambda, Microsoft Azure Stream Analytics, Google Cloud IoT Core 
kullanılabilir. 
 Bulut tabanlı veri depolama için S3 (AWS), Blob Storage (Azure) gibi bulut tabanlı depolama 
hizmetleri, Amazon Redshift, BigQuery kullanılabilir. 
♦ Veri Yönetimi ve Temizleme: 
 Veri temizleme ve dönüştürme için ETL araçları kullanılabilir. Örneğin, Apache Nifi, 
Talend, Informatica. 
 Veri kalitesini artırmak için veri kalitesi araçları kullanılabilir. Örneğin, Trifacta, OpenRefine.
Kaynakça 
❖ https://io.adafruit.com/api/docs/ 
❖ https://platform.openai.com/docs/overview 
❖ Prof. Dr. Cüneyt BAYILMIŞ ve Prof. Dr. Kerem KÜÇÜK, “Nesnelerin İnternet’i: Teori 
ve Uygulamaları”, Papatya Yayınevi, 2019. 
❖ https://app.ciz.io/canvases 
❖ A. Fuqaha, M. Guizani, M. Mohammadi, M. Aledhari, M. Ayyash, “Internet of Things: 
A Survey on Enabling Technologies, Protocols, and Applications”, IEEE 
Communication Survey&Tutorials, vol. 17 (4), 2347-2376, 2015. 
❖ C. Tsai, C. Lai, M. Chiang, and L. T. Yang, “Data mining for Internet of Things: A 
survey,” IEEE Commun. Surveys Tuts., vol. 16, no. 1, pp. 77– 97, 1st Quart, 2014. 
❖ A. Osterwalder, Y. Pigneur, ‘‘Business Model Generation’’, Çev. Melis İnan, 
Optimist Yayım Dağıtım, 2013. 
❖ Chatterjee, J. M., Kumar, R., Khari, M., Hung, D. T., & Le, D. N. (2018). Internet 
of Things based system for Smart Kitchen. International Journal of Engineering and 
Manufacturing, 8(4), 29.
Proje için Bussiness Canvas iş modeli oluşturulmuş, Adafruit.io Dashboard ve devre şeması görselleri eklenmiştir.
