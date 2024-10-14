<!DOCTYPE html>
<html lang="id">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Absensi Siswa</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 20px;
        }
        button {
            display: block;
            margin: 10px 0;
            padding: 10px;
            background-color: #4CAF50;
            color: white;
            border: none;
            cursor: pointer;
        }
        button:hover {
            background-color: #45a049;
        }
        h1 {
            color: #333;
        }
    </style>
</head>
<body>
    <h1>Absensi Siswa</h1>
    <div id="menu">
        <button onclick="displayStudents()">Tampilkan Daftar Siswa</button>
        <button onclick="markLeavePrompt()">Tandai Pulang Siswa</button>
        <button onclick="saveAbsence()">Simpan Data Absensi</button>
        <button onclick="exitApp()">Keluar</button>
    </div>
    <div id="content"></div>

    <script>
        // Data siswa disimpan sebagai array objek
        let students = [
            { name: "Abi", canLeave: true, lastLeaveDate: 0, nextAvailableDate: 0 },
            { name: "Rizal", canLeave: true, lastLeaveDate: 0, nextAvailableDate: 0 },
            { name: "Ramli", canLeave: true, lastLeaveDate: 0, nextAvailableDate: 0 },
            { name: "Sopyan", canLeave: true, lastLeaveDate: 0, nextAvailableDate: 0 },
            { name: "Ardi", canLeave: true, lastLeaveDate: 0, nextAvailableDate: 0 }
        ];

        function displayStudents() {
            let contentDiv = document.getElementById('content');
            contentDiv.innerHTML = "<h3>Daftar Siswa:</h3>";
            students.forEach((student, index) => {
                let lastLeaveDate = student.lastLeaveDate ? new Date(student.lastLeaveDate).toLocaleDateString() : 'Belum pernah pulang';
                let nextAvailableDate = student.nextAvailableDate ? new Date(student.nextAvailableDate).toLocaleDateString() : '-';
                let status = student.canLeave ? "[Bisa Pulang]" : "[Tidak Bisa Pulang]";
                contentDiv.innerHTML += `<p>${index + 1}. ${student.name} [Terakhir Pulang: ${lastLeaveDate}] [Bisa Pulang Lagi: ${nextAvailableDate}] ${status}</p>`;
            });
        }

        function markLeavePrompt() {
            let studentIndex = prompt("Masukkan nomor siswa yang ingin ditandai pulang:");
            studentIndex = parseInt(studentIndex) - 1;

            if (studentIndex >= 0 && studentIndex < students.length) {
                if (!isEligibleToLeave(students[studentIndex])) {
                    alert(`${students[studentIndex].name} tidak bisa pulang karena sudah absen pulang dalam 14 hari terakhir.`);
                } else {
                    markLeave(studentIndex);
                    alert(`${students[studentIndex].name} telah ditandai pulang.`);
                }
            } else {
                alert("Nomor siswa tidak valid.");
            }
        }

        function markLeave(index) {
            let currentTime = Date.now();
            students[index].canLeave = false;
            students[index].lastLeaveDate = currentTime;
            students[index].nextAvailableDate = currentTime + 14 * 24 * 60 * 60 * 1000; // 14 hari dalam milidetik
        }

        function isEligibleToLeave(student) {
            let currentTime = Date.now();
            if (student.lastLeaveDate === 0) {
                return true; // Belum pernah pulang
            }
            let timeDiff = currentTime - student.lastLeaveDate;
            return timeDiff >= 14 * 24 * 60 * 60 * 1000; // 14 hari dalam milidetik
        }

        function saveAbsence() {
            // Menyimpan data dalam Local Storage
            localStorage.setItem('students', JSON.stringify(students));
            alert("Data absensi telah disimpan.");
        }

        function loadAbsence() {
            let savedData = localStorage.getItem('students');
            if (savedData) {
                students = JSON.parse(savedData);
            }
        }

        function exitApp() {
            alert("Keluar dari aplikasi.");
        }

        // Muat data saat aplikasi dimulai
        window.onload = loadAbsence;
    </script>
</body>
</html>