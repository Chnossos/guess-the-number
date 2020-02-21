Packets used in this implementation
===================================

## Server Packets

### Error

```javascript
{
    "error": "Explaination"
}
```

### Game Rules

```javascript
{
    "header": "rules",
    "bounds": "1,100",
    "limit": <int/null>
}
```

### Input Response

```javascript
{
    "header": "answer",
    "answer": "+" / "-" / "="
}
```

### End Game Score

```javascript
{
    "header": "score",
    "attempts": <int>,
    "elapsed_time": <int>
}
```

## Client Packets

### Identity

```javascript
{
    "header": "identity",
    "name": <string/null>
}
```

### Guess Input

```javascript
{
    "header": "guess",
    "guess": <int>
}
```
