<?php
include 'db.php';
session_start();

$error_message = isset($_GET['error']) ? $_GET['error'] : '';


if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = $_POST["name"];


    $stmt = $conn->prepare("SELECT id, name FROM superhero WHERE name = ?");
    $stmt->bind_param("s", $name);
    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows == 1) {
        $hero = $result->fetch_assoc();
        $_SESSION["name"] =  $hero["name"];
        $_SESSION["hero_id"] = $hero["id"];
        header("Location: index.php");
        exit();
    } else {
        echo "Invalid name.";
    }

}


?>


<!DOCTYPE html>
<html>
    <head>
    <title>Index</title>
    </head>
    <body>

        <div class="login-container">
            <h1>please enter you superhero name!</h1>
            <?php if (!empty($error_message)) { ?>
            <p><?php echo $error_message; ?></p>
            <?php } ?>
            <form method="POST" action="">
            <label for="name">Name:</label>
            <input type="text" id="name" name="name" required>
            <br> <br>
            <input type="submit" value="Login">
            </form>
        </div>


        <a href="modify.php" style="margin-right: 10px;">Modify own powers</a> 
        <a href="add.php" style="margin-right: 10px;">Add superhero</a> 
        <a href="displaySuperhero.php" style="margin-right: 10px;">View list of superheros</a>

        <a href="displayTeams.php">View list of teams</a>
    </body>
</html>