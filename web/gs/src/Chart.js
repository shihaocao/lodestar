import React, { useState, useEffect, useRef} from 'react';
import { useTheme } from '@material-ui/core/styles';
import { LineChart, Line, XAxis, YAxis, Label, ResponsiveContainer } from 'recharts';
import Title from './Title';

// Generate Sales Data
function createData(time, amount) {
  return { time, amount };
}

const data = [
  createData('00:00', 0),
  createData('03:00', 300),
  createData('06:00', 600),
  createData('09:00', 800),
  createData('12:00', 1500),
  createData('15:00', 2000),
  createData('18:00', 2400),
  createData('21:00', 2400),
  createData('24:00', undefined),
];

function interleave(times, vals){
  return times.reduce((acc, elem, i) => acc.concat(elem, vals[i]));
}

export default function Chart() {
  const theme = useTheme();

  const [alts, setAlts] = useState(0);

  const t0 = [5,6,7,8]
  const t1 = t0.map(x => x.toString())
  const v2 = [40,50,23,55]

  // setAlts(interleave(t1,v2));

  useEffect(() => {
    setAlts(['0',0,'1',10,'2',2300]);
  }, []);


  console.log(alts);
  // var updateAlts = () => {
  //   fetch('/altitude').then(res => res.json()).then(data => {
  //         setAlts(data.altitude);
  //       });
  // }

  // var updateAlt = () => {
  //   fetch('/altitude').then(res => res.json()).then(data => {
  //     setAlt(data.altitude);
  //   });
  // }

  // setInterval(updateAlt, 0.1);
  // setInterval(updateAlts, 0.1);

  return (
    <React.Fragment>
      <Title>Today</Title>
      <ResponsiveContainer>
        <LineChart
          data={alts}
          margin={{
            top: 16,
            right: 16,
            bottom: 0,
            left: 24,
          }}
        >
          <XAxis dataKey="time" stroke={theme.palette.text.secondary} />
          <YAxis stroke={theme.palette.text.secondary}>
            <Label
              angle={270}
              position="left"
              style={{ textAnchor: 'middle', fill: theme.palette.text.primary }}
            >
              Sales ($)
            </Label>
          </YAxis>
          <Line type="monotone" dataKey="amount" stroke={theme.palette.primary.main} dot={false} />
        </LineChart>
      </ResponsiveContainer>
    </React.Fragment>
  );
}
