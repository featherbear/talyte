export function get (req, res) {
  return res.end(
    JSON.stringify([
      ['network 0', 'BSSID 0', 9],
      ['network 1', 'BSSID 1', 8],
      ['network 2', 'BSSID 2', 7],
      ['network 3', 'BSSID 3', 6],
      ['network 4', 'BSSID 4', 5],
      ['network 5', 'BSSID 5', 4],
      ['network 6', 'BSSID 6', 3],
      ['network 7', 'BSSID 7', 2],
      ['network 8', 'BSSID 8', 1]
    ])
  )
}
