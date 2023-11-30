function dbInit(){
    console.log("Iniciando la BBDD...")
    db = LocalStorage.openDatabaseSync("sqlitedemodb","1.0","SQLite Demo database",100000);
    console.log("BBDD INICIADA")
    db.transaction(function(tx){
        print('...create table')
        tx.executeSql('CREATE TABLE IF NOT EXISTS userstable(username TEXT, score INTEGER, dif TEXT)');
    });
}

function storeData() {
    console.log("STORING DATA...")

    if (!db) return;

    db.transaction(function(tx) {
        // Check if the user entry is available in the userstable
        var result = tx.executeSql('SELECT * FROM userstable WHERE username = ? AND dif = ?', [nameInput.text, difficulty]);

        // Prepare the JSON object data from QML code
        var obj = {
            username: nameInput.text,
            score: points,
            dif: difficulty.toString()
            // Add other properties if needed
        }

        if (result.rows.length === 1) {
            // Check if the new score is higher than the existing score
            var existingScore = parseInt(result.rows.item(0).score);
            if (obj.score > existingScore) {
                // Update only if the new score is higher
                console.log("UPDATING DB TABLE...")
                result = tx.executeSql('UPDATE userstable SET score=? WHERE username=? AND dif=?', [obj.score, obj.username, obj.dif]);
            } else {
                // Do not update if the new score is not higher
                console.log("New score is not higher. Not updating.")
            }
        } else {
            // Insert only if the user and difficulty combination doesn't exist
            console.log("INSERTING INTO DB TABLE...")
            result = tx.executeSql('INSERT INTO userstable (username, score, dif) VALUES (?, ?, ?)', [obj.username, obj.score, obj.dif]);
        }
    });
}


function readingData() {
    console.log("READING ALL USERS...");

    if (!db) return;

    db.transaction(function(tx) {
        print('...READING ALL USERS FROM DB');
        var result = tx.executeSql('SELECT * FROM userstable ORDER BY score DESC');

        myModel.clear(); // Limpiar el modelo antes de actualizarlo

        for (var i = 0; i < result.rows.length; ++i) {
            var rowData = result.rows.item(i);

            // Asegúrate de convertir la cadena a un entero
            var score = parseInt(rowData.score);
            var dif = rowData.dif;
            console.log(dif)
            myModel.append({ username: rowData.username, score: score,dif:dif });
        }
    });
}
