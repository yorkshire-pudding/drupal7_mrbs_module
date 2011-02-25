<?php
/*****************************************************************************\
*                                                                            *
*   File name      session_drupal.inc                                        *
*                                                                            *
*   Description    Manage sessions via cookies stored in the client browser. *
*                  Use Drupal session management instead of MRBS.            *
*                                                                            *
*   URL arguments  None                                                      *
*                                                                            *
*   Notes          To use this session mechanism, set in config.inc.php:     *
*                  $auth["session"]  = "drupal";                             *
*                                                                            *
*   History                                                                  *
*                  2009/02/14 Vesa Palmu Created this file                   *
*                  Remaining history in ChangeLog and CVS logs               *
*                                                                            *
\*****************************************************************************/


if (!user_access('view mrbs')) {
	print t('Permission denied');
	exit;
}

$UserName = $user->name;

function getUserName()
{
  global $user;
  return $user->name;
}

// Print the logon entry on the top banner.
function PrintLogonBox()
{
  global $PHP_SELF, $QUERY_STRING, $user_list_link, $user_link, $day, $month;
  global $year, $auth;
  
  $TargetURL = basename($PHP_SELF);
  if (isset($url_base) && ($url_base != ""))
  {
    $TargetURL = $url_base . '/' . $TargetURL;
  }
  if (isset($QUERY_STRING))
  {
    $TargetURL = $TargetURL . "?" . $QUERY_STRING;
  }
  $user=getUserName();
  if (isset($user))
  {
    // words 'you are xxxx' becomes a link to the
    // report page with only entries created by xxx. Past entries are not
    // displayed but this can be changed
    $search_string = "report.php?From_day=$day&amp;From_month=$month&amp;".
      "From_year=$year&amp;To_day=1&amp;To_month=12&amp;To_year=2030&amp;".
      "areamatch=&amp;roommatch=&amp;namematch=&amp;descrmatch=&amp;summarize=1&amp;".
      "sortby=r&amp;display=d&amp;sumby=d&amp;creatormatch=$user";
?>
      <a name="logonBox" href="<?php echo "$search_string\" title=\""
         . get_vocab('show_my_entries') . "\">
        " . get_vocab('you_are')." "
         .$user ?>
      </a>
  <?php 
  }
  if (isset($user_list_link)) 
  {
    print "<a href=\"$user_list_link\">" . get_vocab('user_list') . "</a>\n";
  }
}

?>
