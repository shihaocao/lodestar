import React, { useState, useEffect, useRef} from 'react';
import Link from '@material-ui/core/Link';
import { makeStyles } from '@material-ui/core/styles';
import Typography from '@material-ui/core/Typography';
import Title from './Title';

function preventDefault(event) {
  event.preventDefault();
}

const useStyles = makeStyles({
  depositContext: {
    flex: 1,
  },
});

export default function Deposits() {
  const classes = useStyles();

  const [ccno, set_ccno] = useState(0);

  const update_ccno = async () => {
    await fetch('/ccno')
      .then(res => res.json())
      .then(data => {
      set_ccno(data.ccno);
    });
  }

  useEffect(() => {
    const interval = setInterval(() => {
      update_ccno();
    }, 100);
    return () => clearInterval(interval);
  }, []);

  return (
    <React.Fragment>
      <Title>Recent Deposits</Title>
      <Typography component="p" variant="h4">
        CCNO: {ccno}
      </Typography>
      <Typography color="textSecondary" className={classes.depositContext}>
        on 15 March, 2019
      </Typography>
      <div>
        <Link color="primary" href="#" onClick={preventDefault}>
          View balance
        </Link>
      </div>
    </React.Fragment>
  );
}
