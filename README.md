# Sumo-Robot
Isi dari repositori ini adalah kode untuk robot sumo yang pernah saya dan tim buat.
Terdapat 2 versi dari robot sumo yang ada pada repo ini yaitu yang menggunakan driver motor yang berupa shield Arduino dengan IC berupa
L293D dan versi yang satunya menggunakan driver motor terpisah dengan IC berupa BTNxxx.

## SumoRobot
SumoRobot merupakan versi yang menggunakan IC BTNxxx. Inti dari kode ini adalah pembacaan sensor dan penggerakan aktuator berupa motor DC.
Pembacaan jarak menggunakan sensor Ultrasonik dan pembacaan garis luar arena berwarna putih menggunakan sensor Infared.
Penggerakan aktuator menggunakan metode PWM sehingga kecepatan dari motor DC dapat diatur.

## SumoRobot_V2
SumoRobot_V2 merupakan versi yang menggunakan IC L293D. Inti dari kode ini sama dengan versi sebelumnya yaitu SumoRobot.
Perubahan pada versi kedua ini adalah dengan penggunaan library **AFMotor** yang dapat mengontrol kecepatan dari motor DC yang dihubungkan
dengan kepada shieldnya. Selain itu terdapat pula tambahan berupa fitur *controlled* yang memungkinkan pengguna dapat mengendalikan robot
melalui aplikasi pada smartphone berupa **Bluetooth RC Controller**.
