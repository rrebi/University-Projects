<?php
require_once 'db.php';
session_start(); 
if (!isset($_SESSION['hero_id'])) {
    $error_message = "Hero ID not found in the session. Please log in as a hero.";
    header("Location: index.php?error=" . urlencode($error_message));
    exit; 
}

if (isset($_SESSION['hero_id'])) {
    $id = $_SESSION['hero_id'];

    $stmt = $conn->prepare("SELECT * FROM superhero WHERE id = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
    $result = $stmt->get_result();
    $hero = $result->fetch_assoc();

    if (!$hero) {
        echo "hero not found.";
        exit();
    }
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $string = $_POST['string'];

    $stmt = $conn->prepare("UPDATE superhero SET powers = ? WHERE id = ?");
    $stmt->bind_param("si", $string, $id);
    $stmt->execute();

    header("Location: displaySuperhero.php");
    exit();
}
?>

<!DOCTYPE html>
<html>
    <head>
    <title>Update powers</title>
    </head>
    <body>
    <h1>Update powers</h1>
    <form method="POST">
        <label for="string">string:</label>
        <input type="text" id="string" name="string" value="<?php echo $hero['powers']; ?>"><br><br>

        <input type="submit" value="Update">
    </form>

    </body>
</html>
