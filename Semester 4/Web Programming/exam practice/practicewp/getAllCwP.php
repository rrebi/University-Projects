<?php
require_once 'db.php';
session_start();

// Fetch all parents from the database
if (isset($_SESSION['parent_id'])) {
    $parentid = $_SESSION['parent_id'];
    $parentname = $_SESSION['username'];
    
    
    if (isset($_GET['string']) && !empty($_GET['string'])) {
        $string = $_GET['string'];

        // Prepare the query to fetch parents with matching children
        $stmt = $conn->prepare("SELECT c.id, c.string, c.date
        FROM child c WHERE c.idP = ? AND c.date= ?");
        $stmt->bind_param("ss", $parentid, $string);
        $stmt->execute();
        $result = $stmt->get_result();
        $children = $result->fetch_all(MYSQLI_ASSOC);
    } else{

        // Prepare the query to fetch parents with matching children
        $stmt = $conn->prepare("SELECT c.id, c.string, c.date
                                FROM child c WHERE c.idP = ?");
       $stmt->bind_param("s", $parentid);
       $stmt->execute();
       $result = $stmt->get_result();
       $children = $result->fetch_all(MYSQLI_ASSOC);
    }
} 


?>

<!DOCTYPE html>
<html>
<head>
  <title>All Children of the Parent</title>
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
  <h1>All Children</h1>

   <form method="GET" action="">
    <label for="string">Enter a value for 'string':</label>
    <input type="date" id="string" name="string"> 
    <input type="submit" value="Fetch Children">
  </form>


<?php if(empty($parentid)){ ?>  
    <p>No parent found./not logged in</p>
    <a href="login.php">Login</a>
  <?php } elseif(empty($children)) { ?>
    <p>No records found.</p>
  <?php } else {?>
  <table>
    <tr>
      <th>ID</th>
      <th>String</th>
      <th>Parent</th>
      <th>Actions</th>
    </tr>
    <?php foreach ($children as $child) { ?>
    <tr>
      <td><?php echo $child['id']; ?></td>
      <td><?php echo $child['string']; ?></td>
      <td><?php echo $parentname; ?></td>
      
      <td>
        <a href="update.php?id=<?php echo $child['id']; ?>">Update</a> |
        <a href="delete.php?id=<?php echo $child['id']; ?>">Delete</a>
      </td>
    </tr>
    <?php } ?>
  </table>
    <?php } ?>
</body>
</html>