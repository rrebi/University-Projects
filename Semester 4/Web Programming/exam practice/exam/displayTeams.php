<?php

require 'db.php';
if (isset($_GET['string']) && !empty($_GET['string'])) {
    
    $string = $_GET['string'];

    //get superheros
    $stmt = $conn->prepare('SELECT name FROM superhero WHERE powers LIKE ?');

    $searchString = "%{$string}%";     
    $stmt->bind_param("s", $searchString);
    $stmt->execute();
    $result = $stmt->get_result();
    $heros = $result->fetch_all(MYSQLI_ASSOC);


    foreach ($heros as $h){
        $stmt = $conn->prepare('SELECT * FROM team 
                                where superherosList LIKE ?');
    
        $searchString = "%{$h}%";    
        $stmt->bind_param("s", $searchString);
        $stmt->execute();
        $result = $stmt->get_result();
        $herosList = $result->fetch_all(MYSQLI_ASSOC);
    }

} 

?>

<!DOCTYPE html>
<html>
<head>
  <title>All Parents</title>
  <style>
    table {
      border-collapse: collapse;
      width: 100%;
    }
    th, td {
      border: 1px solid black;
      padding: 8px;
      text-align: center;
    }
  </style>
</head>
<body>
  <h1>All Superheros</h1>

  <form method="GET" action="">
    <label for="string">Enter a value for 'power':</label>
    <input type="text" id="string" name="string"> 
    <input type="submit" value="Fetch superheros">
  </form>

  <?php if (empty($heros)) { ?>
    <p>No records found.</p>
  <?php } else { ?>
  <table>
    <tr>
      <th>ID</th>
      <th>Name</th>
      <th>Powers</th>
    </tr>
    <?php foreach ($herosList as $hero) { ?>
    <tr>
      <td><?php echo $hero['id']; ?></td>
      <td><?php echo $hero['name']; ?></td>
      <td><?php echo $hero['superheroList']; ?></td>
      
      
    </tr>
    <?php } ?>
  </table>
    <?php } ?>
</body>
</html>

