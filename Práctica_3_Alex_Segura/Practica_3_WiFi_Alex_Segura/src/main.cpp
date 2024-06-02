#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "vodafone52C8"; // Ingresa tu SSID aquí
const char* password = "DZ4EWZLNMN4UZN"; // Ingresa tu contraseña aquí

WebServer server(80); // Objeto de WebServer (puerto HTTP, 80 es el predeterminado)

// HTML contenido que se muestra en el servidor web
String HTML = "<!DOCTYPE html>\
<html lang='es'>\
<head>\
    <meta charset='UTF-8'>\
    <meta name='viewport' content='width=device-width, initial-scale=1.0'>\
    <title>Tipos de Guitarras</title>\
    <style>\
        body {\
            font-family: Arial, sans-serif;\
            margin: 20px;\
        }\
        h1 {\
            color: #333;\
        }\
        h2 {\
            color: #444;\
        }\
        p {\
            color: #666;\
        }\
        ul {\
            list-style-type: none;\
            padding: 0;\
        }\
        li {\
            margin-bottom: 10px;\
        }\
    </style>\
</head>\
<body>\
    <h1>LA GUITARRA</h1>\
    \
    <h2>Introducción</h2>\
    <p>La guitarra es uno de los instrumentos musicales más populares del mundo. A lo largo de los siglos, ha evolucionado en diversos tipos, cada uno con sus propias características y aplicaciones.</p>\
    \
    <h2>Historia</h2>\
    <p>La historia de la guitarra se remonta a miles de años atrás. Se cree que sus orígenes se encuentran en la antigua Persia, donde se desarrollaron instrumentos de cuerda similares. Con el tiempo, la guitarra se ha transformado y adaptado en diferentes culturas y épocas, dando lugar a una amplia variedad de estilos y diseños.</p>\
    \
    <h2>Tipos de Guitarras</h2>\
    <p>A continuación se presentan algunos de los tipos más comunes de guitarras:</p>\
    <ul>\
        <li><strong>Guitarra Acústica:</strong> Perfecta para tocar en cualquier lugar sin necesidad de amplificación.</li>\
        <li><strong>Guitarra Eléctrica:</strong> Ideal para estilos de música más eléctricos y se puede conectar a amplificadores para aumentar su sonido.</li>\
        <li><strong>Guitarra Clásica:</strong> Con cuerdas de nylon, es adecuada para estilos de música clásica y flamenco.</li>\
        <li><strong>Guitarra Semiacústica:</strong> Combina características de la guitarra eléctrica y la acústica, proporcionando un sonido más cálido.</li>\
        <li><strong>Guitarra de 12 Cuerdas:</strong> Tiene el doble de cuerdas que una guitarra estándar, lo que produce un sonido más rico y completo.</li>\
        <li><strong>Guitarra Resonadora:</strong> Utiliza un cono metálico para amplificar el sonido, siendo común en estilos de blues y country.</li>\
    </ul>\
    \
    <h2>Cómo Elegir la Guitarra Correcta</h2>\
    <p>Al elegir una guitarra, es importante considerar factores como el estilo de música que deseas tocar, tu nivel de experiencia y tu presupuesto. También es recomendable probar diferentes guitarras antes de tomar una decisión final.</p>\
    \
    <h2>Mantenimiento y Cuidado</h2>\
    <p>Para mantener tu guitarra en óptimas condiciones, es importante limpiarla regularmente, cambiar las cuerdas cuando sea necesario y almacenarla en un lugar seguro y adecuado.</p>\
    \
    <h2>Conclusión</h2>\
    <p>La guitarra es un instrumento versátil y emocionante que ha capturado la imaginación de músicos y aficionados de todo el mundo. Con una amplia variedad de tipos disponibles, siempre hay una guitarra adecuada para cada persona y estilo de música.</p>\
    \
    <a href='https://ibb.co/0J5jQsC'><img src='https://i.ibb.co/KynjmK2/Guitarras.jpg' alt='Guitarras' border='0'></a><br /><a target='_blank' href='https://es.imgbb.com/'>pics para editar</a><br />\
</body>\
</html>";


// Manejar la URL raíz (/)
void handle_root() {
    server.send(200, "text/html", HTML);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Intentando conectar a ");
    Serial.println(ssid);
    
    // Conectar al modem de Wi-Fi
    WiFi.begin(ssid, password);
    
    // Verificar que se haya conectado a la red Wi-Fi
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("Conexión Wi-Fi exitosa");
    Serial.print("IP asignada: ");
    Serial.println(WiFi.localIP()); // Mostrar la IP de ESP32 en serie
    
    server.on("/", handle_root);
    server.begin();
    Serial.println("Servidor HTTP iniciado");
    delay(100);
}

void loop() {
    server.handleClient();
}
