<?php
/*****************************************************************************
*
*   File name       auth_db_ext.inc
*
*   Description     Authenticate users from a table in another database.
*
*   Notes           To use this authentication scheme, set in config.inc.php:
*         $auth["type"]  = "db_ext";
*                   Assumes passwords are stored in the other table in
*                   plaintext, authValidateUser() will need to be changed if
*                   the password is stored differently.
*
*   History
*    Available in the source control system
*
******************************************************************************/
// $Id$

/* authValidateUser($user, $pass)
 * 
 * Checks if the specified username/password pair are valid
 * 
 * $user  - The user name
 * $pass  - The password
 * 
 * Returns:
 *   0        - The pair are invalid or do not exist
 *   non-zero - The pair are valid
 */

//for drupal7 method autentication functions password.inc and bootstrap.inc are needed. The route we use is when we install MRBS as a Drupal subdirectory (drupal/mrbs/web)

include ("../../includes/password.inc");
include ("../../includes/bootstrap.inc");

function authValidateUser($user, $pass)
{
  global $auth;

  $retval = 0;

  $user = strtolower($user);

  if (empty($auth['drupal']['db_system']))
  {
    $auth['drupal']['db_system'] = 'mysql';
  }

  $conn = sql_connect($auth['drupal']['db_system'],
                      $auth['drupal']['db_host'],
                      $auth['drupal']['db_username'],
                      $auth['drupal']['db_password'],
                      $auth['drupal']['db_name']);

  $user = addslashes($user);
  //we use default D7 table names here
  $query = "SELECT pass FROM users WHERE name ='$user'";

  $r = sql_query($query, $conn);

  if ($r && (sql_count($r, $conn) == 1)) // force a unique match
  {
    $row = sql_row($r, 0, $conn);
    $password_to_compare->pass = $row[0];     
    if (user_check_password($pass,$password_to_compare))
     {
       $retval = 1;
     }
   }
  return $retval;
}

/* authGetUserLevel($user)
 * 
 * Determines the users access level
 * 
 * $user - The user name
 *
 * Returns:
 *   The users access level
 */
function authGetUserLevel($user)
{
  global $auth;
  
  $conn = sql_connect($auth['drupal']['db_system'],
                      $auth['drupal']['db_host'],
                      $auth['drupal']['db_username'],
                      $auth['drupal']['db_password'],
                      $auth['drupal']['db_name']);
  $user = addslashes($user);
  //we use default D7 table names here to take rid of every mrbs role
  $query = "SELECT rid FROM role WHERE name = 'mrbs admin'";
  $r = sql_query($query, $conn);
  if ($r && (sql_count($r, $conn) == 1)) // force a unique match
  {
    $row = sql_row($r, 0, $conn);
    $mrbs_admin_rid = $row[0];     
  }
  $query_2 = "SELECT rid FROM role WHERE name = 'mrbs bookings'";
  $r_2 = sql_query($query_2, $conn);
  if ($r_2 && (sql_count($r_2, $conn) == 1)) // force a unique match
  {
    $row_2 = sql_row($r_2, 0, $conn);
    $mrbs_bookings_rid = $row_2[0];
  }
  $query_3 = "SELECT rid FROM role WHERE name = 'mrbs view'";
  $r_3 = sql_query($query_3, $conn);
  if ($r_3 && (sql_count($r_3, $conn) == 1)) // force a unique match
  {
    $row_3 = sql_row($r_3, 0, $conn);
    $mrbs_view_rid = $row_3[0];    
  }
  //we use default D7 table names here to take uid of the user
  $query_4 = "SELECT uid FROM users WHERE name = '$user'";
  $r_4 = sql_query($query_4, $conn);
  $row_4 = sql_row($r_4, 0, $conn);
  $user_uid = $row_4[0];       
  
  //we use default D7 table names here to take all the rid of the user in array
  $query_5 = "SELECT rid FROM users_roles WHERE uid = '$user_uid'";
  $r_5 = sql_query($query_5, $conn);
  for ($i = 0; ($row_5 = sql_row($r_5, $i, $conn)); $i++)
  {
    $rid_array[] = $row_5[0];
  }
  //we compare the rid of the user to check if have mrbs roles
  if(in_array($mrbs_admin_rid, array_values($rid_array))){
  //admin permisions
  return 2;
  }
  elseif(in_array($mrbs_bookings_rid, array_values($rid_array))){
  //booking permisions
  return 1;
  }
  elseif(in_array($mrbs_view_rid, array_values($rid_array))){
  //view permisions
  return 0;
  }
  else{
  //can't access to MRBS
  return -1;
  }
}

?>
